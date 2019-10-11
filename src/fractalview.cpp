// Standard C++ headers

#include <stdio.h>
#include <math.h>

// Qt headers

#include <qapplication.h>
#include <qcolor.h>
#include <qkeycode.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qpainter.h>

// Application headers

#include "fractalview.h"
#include "Fractal.h"
#include "fractalobserver.h"
#include "statesupplier.h"
#include "state.h"
#include "qinfiniteloopcallback.h"
#include "rowsupplier.h"
#include "dmemory.h"

/*****************************************************************************
 * Local Classes
 *****************************************************************************/

class QImageRowSupplier : public RowSupplier
{
   public:
      QImageRowSupplier(QImage *image);
      ~QImageRowSupplier();
      unsigned char *nextRow(InfiniteLoopCallback *callback);
      int getWidth();
      int getHeight();

   private:
      QImage *mImage;
      unsigned char *mBuffer;
      int mWidth;
      int mHeight;
      int mRow;
};

QImageRowSupplier::QImageRowSupplier(QImage *image) :
   mImage(image),
   mBuffer(0),
   mRow(0)
{
   mWidth  = mImage->width();
   mHeight = mImage->height();

   DNEW(mBuffer, unsigned char[3 * mWidth]);
}

QImageRowSupplier::~QImageRowSupplier()
{
   DADELETE(mBuffer);
}

unsigned char *QImageRowSupplier::nextRow(InfiniteLoopCallback *)
{
   unsigned char *row = mBuffer;

   if(mRow >= mHeight)
      row = NULL;

   else
   {
      QRgb *ptr = (QRgb *)mImage->scanLine(mRow);

      for(int i = 0, j = 0; i < mWidth; i ++)
      {
         mBuffer[j++] = qRed(ptr[i]);
         mBuffer[j++] = qGreen(ptr[i]);
         mBuffer[j++] = qBlue(ptr[i]);
      }

      mRow++;
   }

   return(row);
}

int QImageRowSupplier::getWidth()
{
   return(mWidth);
}

int QImageRowSupplier::getHeight()
{
   return(mHeight);
}

/*****************************************************************************
 * Local Functions
 *****************************************************************************/

double distance(double x0, double y0, double x1, double y1)
{
   double x = x0 - x1;
   double y = y0 - y1;

   return(sqrt(x * x + y * y));
}

FractalView::FractalView(
   QWidget *parent,
   const char * name,
   WFlags f
)
   :
   QScrollView(parent, name, f),
   mPixmap(0),
   mImage(0),
   mStopped(0),
   mState(STATE_INITIAL),
   mX0(0.0),
   mY0(0.0),
   mX1(0.0),
   mY1(0.0),
   mXCurrent(0.0),
   mYCurrent(0.0),
   mWidth(0),
   mHeight(0),
   mSupplier(0),
   mObserver(0),
   mZoomRed(0),
   mZoomGreen(0),
   mZoomBlue(0),
   mConstrained(FALSE),
   mConstrainedWidth(0.0),
   mConstrainedHeight(0.0),
   mExpectingMousePress(FALSE)
{
   // Allow our widget to get focus - this is required if we are
   // to receive keyboard events

   setFocusPolicy(QWidget::StrongFocus);
}

void FractalView::newFractal(
   Fractal *ptr,
   FractalObserver *observer,
   StateSupplier *supplier
)
{
   mState                = STATE_INITIAL;
   mX0 = mX1 = mY0 = mY1 = 0.0;
   mXCurrent = mYCurrent = 0.0;

   mStopped = 0;

   if(mPixmap)
   {
      QPainter p1(mPixmap);

      p1.fillRect(
         0, 0, mPixmap->width(), mPixmap->height(), colorGroup().dark()
      );

      p1.end();
   }

   // Set our size to match that of the supplied
   // fractal

   mWidth  = ptr->getWidth();
   mHeight = ptr->getHeight();

   resizeContents(mWidth, mHeight);

   if(mPixmap)
      DDELETE(mPixmap);

   if(mImage)
      DDELETE(mImage);

   // Create our background pixmap and fill it with black

   DNEW(mPixmap, QPixmap(mWidth, mHeight));

   QPainter p1(mPixmap);
   p1.fillRect(0, 0, mWidth, mHeight, QColor(0, 0, 0));
   p1.end();

   // Now create our image - we'll draw our scanlines into this

   DNEW(mImage, QImage(mWidth, mHeight, 32));

   // Save off our ConstraintSupplier and FractalObserver pointers

   mSupplier = supplier;
   mObserver = observer;

   // Get ready to draw, and notify our observer that drawing has begun

   ptr->begin();
   mObserver->drawingStarted();

   QInfiniteLoopCallback callback(&mStopped);
   QPainter p;

   for(int i = 0; i < mHeight; i ++)
   {
      unsigned char *row = ptr->nextRow(&callback);

      if(mStopped)
         break;

      uint *data = (uint *)mImage->scanLine(i);

      for(int j = 0, k = 0; j < mWidth; j ++, data ++, k += 3)
         *data = qRgb(row[k], row[k + 1], row[k + 2]);

      double percentage = 100.0 * (double)i / (mHeight - 1);
      mObserver->percentComplete(percentage);

      // Draw the image to our pixmap, note that previously (above the
      // for loop) we had:
      //
      //    QPainter p(mPixmap);
      //
      // and we never bothered with calling 'p.end()' (we just let the
      // destructor handle it for us.
      //
      // Anyway, at some point during the Qt 2.x experience fractorama began
      // manifesting black horizontal lines in the image area (which were
      // particularly likely to occur if you agitated the main window while
      // drawing was going on).  This was never a problem on win32 but
      // was consistently occurring on linux.  After a fair bit of digging
      // I found (in the QPainter documentation) a warning that you can't
      // draw a QPixmap while it is being painted so I sandwiched the
      // call to 'drawImage' between begin(mPixmap) and end() and that seems
      // to have done the trick

      p.begin(mPixmap);
      p.drawImage(0, i, *mImage, 0, i, mWidth, 1);
      p.end();

      // Now draw the screen

      repaint();

      // Now give our app a chance to respond to events

      qApp->processEvents();
   }

   if(mStopped)
   {
      mObserver->drawingFinished("Drawing Aborted", TRUE);
   }
   else
   {
      char s[512] = { '\0' };

      strcpy(s, "Drawing Complete");

      int count = ptr->getInvalidColorCount();

      if(count > 0)
      {
         sprintf(
            s + strlen(s),
            " (%d invalid color %s)",
            count,
            (count > 1 ? "values" : "value")
        );
      }

      mObserver->drawingFinished(s, FALSE);
   }

   // We're done - whether the drawing has completed or not, zooming is now
   // allowed.  Set our state variables and dispose of the fractal

   mState               = STATE_READY;
   mExpectingMousePress = TRUE;

   DDELETE(ptr);
}

FractalView::~FractalView()
{
   if(mPixmap)
      DDELETE(mPixmap);

   if(mImage)
      DDELETE(mImage);
}

void FractalView::stop()
{
   mStopped = 1;
}

void FractalView::paintEvent(QPaintEvent *ptr)
{
   viewportPaintEvent(ptr);
}

void FractalView::drawContentsOffset(
   QPainter *p,
   int ox, int oy,
   int, int, int, int
)
{
   if(mPixmap)
   {
      p->drawPixmap(-ox, -oy, *mPixmap);

      if(mState != STATE_INITIAL)
      {
         // We have an active zoom rectangle

         int x0 = (int)(mX0 + 0.5);
         int y0 = (int)(mY0 + 0.5);
         int x1 = (int)(mX1 + 0.5);
         int y1 = (int)(mY1 + 0.5);

         int x = (x0 < x1 ? x0 : x1);
         int y = (y0 < y1 ? y0 : y1);
         int w = x1 - x0;
         int h = y1 - y0;

         if(w < 0) w = -w;
         if(h < 0) h = -h;

         p->setPen(QColor(mZoomRed, mZoomGreen, mZoomBlue));
         p->drawRect(x - ox, y - oy, w, h);

         // Only draw the handles if we've got a current zoom rectangle
         // and if both the height and width are large enough to
         // display the handles without overlap
         // JFD - Note: 3.5 is a bit too pessimistic when we're
         // in constrained mode

         if(mState == STATE_ACTIVE &&
            w >= (3.5 * RECT_SIZE) && h >= (3.5 * RECT_SIZE))
         {
            // Get our corner coordinates

            int x0 = (x - ox);
            int x2 = (x - ox) + w - RECT_SIZE;
            int y0 = (y - oy);
            int y2 = (y - oy) + h - RECT_SIZE;

            // Are we in constrained mode?

            if(mConstrained)
            {
               int regions[][2] =
               {
                  { x0, y0 }, { x2, y0 },
                  { x0, y2 }, { x2, y2 },
               };

               int size = sizeof(regions) / sizeof(regions[0]);

               for(int i = 0; i < size; i ++)
               {
                  p->fillRect(
                     QRect(
                        regions[i][0],
                        regions[i][1],
                        RECT_SIZE,
                        RECT_SIZE
                     ),
                     QColor(mZoomRed, mZoomGreen, mZoomBlue)
                  );
               }
            }
            else
            {
               // Get the top, bottom, left and right coordinates

               int y1 = (y - oy) + (h / 2) - (RECT_SIZE / 2);
               int x1 = (x - ox) + (w / 2) - (RECT_SIZE / 2);

               int regions[][2] =
               {
                  { x0, y0 }, { x1, y0 }, { x2, y0 },
                  { x0, y1 },             { x2, y1 },
                  { x0, y2 }, { x1, y2 }, { x2, y2 },
               };

               int size = sizeof(regions) / sizeof(regions[0]);

               for(int i = 0; i < size; i ++)
               {
                  p->fillRect(
                     QRect(
                        regions[i][0],
                        regions[i][1],
                        RECT_SIZE,
                        RECT_SIZE
                     ),
                     QColor(mZoomRed, mZoomGreen, mZoomBlue)
                  );
               }
            }
         }
      }
   }
}

void FractalView::viewportPaintEvent(QPaintEvent* pe)
{
   QScrollView::viewportPaintEvent(pe);
}

void FractalView::viewportMousePressEvent(QMouseEvent *e)
{
   double xValue = (double)(e->x() + contentsX());
   double yValue = (double)(e->y() + contentsY());

   if(mState == STATE_READY)
   {
      // Starting a new zoom rectangle

      mX0 = mX1 = clipX(xValue);
      mY0 = mY1 = clipY(yValue);

      setConstraints();

      mExpectingMousePress = FALSE;
   }

   else if(mState == STATE_ACTIVE)
   {
      // A zoom rectangle exists already

      double x = xValue;
      double y = yValue;

      // We're either:
      //   (a) outside our zoom rectangle in which case we'll
      //       be starting a new zoom rectangle
      //   (b) inside the zoom rectangle and within RECT_SIZE of
      //       one of our "hot-spots" in which case we're resizing
      //       the zoom rectangle
      //   (c) inside the zoom rectangle but not within a corner
      //       in which case we're moving the zoom rectangle

      // We assume that mX0 < mX1 and mY0 < mY1 since the transition
      // to STATE_ACTIVE ensures this relation will hold

      if(x < mX0 || x > mX1 || y < mY0 || y > mY1)
      {
         // We're outside our zoom rectangle

         mState = STATE_READY;

         mX0 = mX1 = clipX(x);
         mY0 = mY1 = clipY(y);
      }
      else
      {
         // Set up some convenience variables

         double xCenter = (mX0 + mX1) / 2.0;
         double yCenter = (mY0 + mY1) / 2.0;

         double xCenterLeft  = xCenter - (RECT_SIZE / 2.0);
         double xCenterRight = xCenter + (RECT_SIZE / 2.0);

         double yCenterTop    = yCenter - (RECT_SIZE / 2.0);
         double yCenterBottom = yCenter + (RECT_SIZE / 2.0);

         // Ultimately (x, y) will be mXCurrent and mYCurrent -
         // the only thing at issue here is which mode we'll
         // end up in so go ahead and assign mXCurrent/mYCurrent now

         mXCurrent = x;
         mYCurrent = y;

         // Classify the clicked point vertically

         enum { V_NONE, V_TOP, V_CENTER, V_BOTTOM };

         int vertical = V_NONE;

         if(y <= mY0 + RECT_SIZE)
            vertical = V_TOP;

         else if(y >= yCenterTop && y <= yCenterBottom)
         {
            // This classification is only available if we are not
            // in constrained mode

            if(!mConstrained)
               vertical = V_CENTER;
         }

         else if(y >= mY1 - RECT_SIZE)
            vertical = V_BOTTOM;

         // Classify the clicked point horizontally

         enum { H_NONE, H_LEFT, H_CENTER, H_RIGHT };

         int horizontal = H_NONE;

         if(x <= mX0 + RECT_SIZE)
            horizontal = H_LEFT;

         else if(x >= xCenterLeft && x <= xCenterRight)
         {
            // This classification is only available if we are not
            // in constrained mode

            if(!mConstrained)
               horizontal = H_CENTER;
         }

         else if(x >= mX1 - RECT_SIZE)
            horizontal = H_RIGHT;

         // Top of zoom rectangle chosen

         if(horizontal == H_LEFT && vertical == V_TOP)
         {
            mState = STATE_RESIZE_LT;
         }

         else if(horizontal == H_CENTER && vertical == V_TOP)
         {
            mState = STATE_RESIZE_CT;
         }

         else if(horizontal == H_RIGHT && vertical == V_TOP)
         {
            mState = STATE_RESIZE_RT;
         }

         // Left or right center of zoom rectangle chosen

         else if(horizontal == H_LEFT && vertical == V_CENTER)
         {
            mState = STATE_RESIZE_LC;
         }

         else if(horizontal == H_RIGHT && vertical == V_CENTER)
         {
            mState = STATE_RESIZE_RC;
         }

         // Bottom of zoom rectangle chosen

         else if(horizontal == H_LEFT && vertical == V_BOTTOM)
         {
            mState = STATE_RESIZE_LB;
         }

         else if(horizontal == H_CENTER && vertical == V_BOTTOM)
         {
            mState = STATE_RESIZE_CB;
         }

         else if(horizontal == H_RIGHT && vertical == V_BOTTOM)
         {
            mState = STATE_RESIZE_RB;
         }

         else
         {
            mState = STATE_MOVE;
         }
      }
   }
}

void FractalView::viewportMouseMoveEvent(QMouseEvent *e)
{
   if(mExpectingMousePress)
      return;

   int doRepaint = 1;
   double x      = (double)(e->x() + contentsX());
   double y      = (double)(e->y() + contentsY());

   switch(mState)
   {
      case STATE_READY:
      {
         // Continue drawing our zoom rectangle if it is within
         // our drawing area

         mX1 = clipX(x);
         mY1 = clipY(y);

         applyConstraints(&mX1, &mY1, mX0, mY0);
      }
      break;

      case STATE_RESIZE_LT:
      {
         mX0 = clipX(mX0, x - mXCurrent);
         mY0 = clipY(mY0, y - mYCurrent);

         applyConstraints(&mX0, &mY0, mX1, mY1);

         mXCurrent = x;
         mYCurrent = y;

         applyConstraints(&mXCurrent, &mYCurrent, mX1, mY1);
      }
      break;

      case STATE_RESIZE_CT:
      {
         mY0       = clipY(mY0, y - mYCurrent);
         mYCurrent = y;

         // This handle won't be shown in constrained mode
      }
      break;

      case STATE_RESIZE_RT:
      {
         mX1 = clipX(mX1, x - mXCurrent);
         mY0 = clipY(mY0, y - mYCurrent);

         applyConstraints(&mX1, &mY0, mX0, mY1);

         mXCurrent = x;
         mYCurrent = y;

         applyConstraints(&mXCurrent, &mYCurrent, mX0, mY1);
      }
      break;

      case STATE_RESIZE_LC:
      {
         mX0       = clipX(mX0, x - mXCurrent);
         mXCurrent = x;

         // This handle won't be shown in constrained mode
      }
      break;

      case STATE_RESIZE_RC:
      {
         mX1       = clipX(mX1, x - mXCurrent);
         mXCurrent = x;

         // This handle won't be shown in constrained mode
      }
      break;

      case STATE_RESIZE_LB:
      {
         mX0 = clipX(mX0, x - mXCurrent);
         mY1 = clipY(mY1, y - mYCurrent);

         applyConstraints(&mX0, &mY1, mX1, mY0);

         mXCurrent = x;
         mYCurrent = y;

         applyConstraints(&mXCurrent, &mYCurrent, mX1, mY0);
      }
      break;

      case STATE_RESIZE_CB:
      {
         mY1       = clipY(mY1, y - mYCurrent);
         mYCurrent = y;

         // This handle won't be shown in constrained mode
      }
      break;

      case STATE_RESIZE_RB:
      {
         mX1 = clipX(mX1, x - mXCurrent);
         mY1 = clipY(mY1, y - mYCurrent);

         applyConstraints(&mX1, &mY1, mX0, mY0);

         mXCurrent = x;
         mYCurrent = y;

         applyConstraints(&mXCurrent, &mYCurrent, mX0, mY0);
      }
      break;

      case STATE_MOVE:
      {
         double xOffset = x - mXCurrent;
         double yOffset = y - mYCurrent;
         double width   = (double)contentsWidth();
         double height  = (double)contentsHeight();

         if(mX0 + xOffset >= 0.0 && mX0 + xOffset <= width &&
            mX1 + xOffset >= 0.0 && mX1 + xOffset <= width)
         {
            mX0 += xOffset;
            mX1 += xOffset;
         }

         if(mY0 + yOffset >= 0.0 && mY0 + yOffset <= height &&
            mY1 + yOffset >= 0.0 && mY1 + yOffset <= height)
         {
            mY0 += yOffset;
            mY1 += yOffset;
         }

         mXCurrent = x;
         mYCurrent = y;
      }
      break;

      default:
      {
         doRepaint = 0;
      }
      break;
   }

   if(doRepaint)
   {
      repaint();
   }
}

void FractalView::viewportMouseReleaseEvent(QMouseEvent *e)
{
   if(mExpectingMousePress)
      return;

   // We've already got all the logic for the various cases
   // in viewportMouseMoveEvent so we delegate most of
   // viewportMouseReleaseEvent's responsibilities to
   // that method

   viewportMouseMoveEvent(e);

   switch(mState)
   {
      // For all the following states, we'll either go to
      // STATE_ACTIVE (if height and width of the zoom rectangle
      // are both > 0.0) or STATE_READY (if at least one of the
      // dimensions is zero

      case STATE_READY    :
      case STATE_RESIZE_LT:
      case STATE_RESIZE_CT:
      case STATE_RESIZE_RT:
      case STATE_RESIZE_LC:
      case STATE_RESIZE_RC:
      case STATE_RESIZE_LB:
      case STATE_RESIZE_CB:
      case STATE_RESIZE_RB:
      case STATE_MOVE     :
      {
         if(mX0 != mX1 && mY0 != mY1)
         {
            if(mState == STATE_READY)
            {
               // Let our observer known that zooming is allowed

               mObserver->zoomAllowed();
            }

            mState = STATE_ACTIVE;

            // As we transition to STATE_ACTIVE it is also our
            // responsibility to canonicalize the zoom rectangle
            // points

            if(mX0 > mX1)
            {
               double temp = mX0;
               mX0         = mX1;
               mX1         = temp;
            }

            if(mY0 > mY1)
            {
               double temp = mY0;
               mY0         = mY1;
               mY1         = temp;
            }

            // Request focus so that key press events can
            // be processed

            setFocus();
         }
         else
         {
            mX0 = mY0 = mX1 = mY1 = 0;
            mState = STATE_READY;

            // Inform our observer that zooming is no longer allowed

            mObserver->zoomNotAllowed();
         }

         repaint();
      }
   }
}

void FractalView::keyReleaseEvent(QKeyEvent *e)
{
   switch(mState)
   {
      // KeyPress events are ignored unless we've got a currently
      // active zoom rectangle

      case STATE_ACTIVE:
      {
         int doRepaint = 0;

         switch(e->key())
         {
            case Key_Left:
            {
               if(mX0 > 0 && mX1 > 0)
               {
                  mX0 -= 1.0;
                  mX1 -= 1.0;

                  doRepaint = 1;
               }
            }
            break;

            case Key_Up:
            {
               if(mY0 > 0 && mY1 > 0)
               {
                  mY0 -= 1.0;
                  mY1 -= 1.0;

                  doRepaint = 1;
               }
            }
            break;

            case Key_Right:
            {
               if(mX0 < contentsWidth() && mX1 < contentsWidth())
               {
                  mX0 += 1.0;
                  mX1 += 1.0;

                  doRepaint = 1;
               }
            }
            break;

            case Key_Down:
            {
               if(mY0 < contentsHeight() && mY1 < contentsHeight())
               {
                  mY0 += 1.0;
                  mY1 += 1.0;

                  doRepaint = 1;
               }
            }
            break;
         }

         if(doRepaint)
            repaint();
      }
      break;
   }
}

int FractalView::getZoomCoordinates(
   double *x0Ptr, double *y0Ptr, double *x1Ptr, double *y1Ptr
)
{
   if(mState != STATE_INITIAL)
   {
      *x0Ptr = mX0;
      *y0Ptr = mY0;
      *x1Ptr = mX1;
      *y1Ptr = mY1;

      return(TRUE);
   }

   return(FALSE);
}

double FractalView::clipX(double x, double offset) const
{
   double value = x + offset;
   double width = (double)contentsWidth();

   return(value < 0.0 ? 0.0 : value > width ? width : value);
}

double FractalView::clipY(double y, double offset) const
{
   double value  = y + offset;
   double height = (double)contentsHeight();

   return(value < 0.0 ? 0.0 : value > height ? height : value);
}

void FractalView::setConstraints()
{
   // Determine if we're in constrained mode
   // or not and if we are, what our constraint values are

   State *state             = mSupplier->getState();
   double constrainedWidth  = 0.0;
   double constrainedHeight = 0.0;

   switch(state->getZoomInWidthOption())
   {
      case ZoomInDialog::USE_PARENT_WIDTH:
      {
         constrainedWidth = (double)mWidth;
      }
      break;

      case ZoomInDialog::USER_SPECIFIED_WIDTH:
      {
         constrainedWidth = (double)state->getZoomInWidth();
      }
      break;

      default:
      {
      }
      break;
   }

   switch(state->getZoomInHeightOption())
   {
      case ZoomInDialog::USE_PARENT_HEIGHT:
      {
         constrainedHeight = (double)mHeight;
      }
      break;

      case ZoomInDialog::USER_SPECIFIED_HEIGHT:
      {
         constrainedHeight = (double)state->getZoomInHeight();
      }
      break;

      default:
      {
      }
      break;
   }

   if(constrainedWidth > 0.0 && constrainedHeight > 0.0)
   {
      mConstrainedWidth  = constrainedWidth;
      mConstrainedHeight = constrainedHeight;
      mConstrained       = TRUE;
   }
   else
   {
      mConstrainedWidth  = 0.0;
      mConstrainedHeight = 0.0;
      mConstrained      = FALSE;
   }
}

void FractalView::applyConstraints(
   double *xNewPtr, double *yNewPtr,
   double x, double y
)
{
   if(mConstrained)
   {
      double x1    = 0.0;
      double y1    = 0.0;
      double x2    = 0.0;
      double y2    = 0.0;
      double slope = 0.0;

      if((*xNewPtr >= x && *yNewPtr >= y) ||
         (*xNewPtr <= x && *yNewPtr <= y))
      {
         slope  = mConstrainedHeight / mConstrainedWidth;
      }
      else
      {
         slope  = -mConstrainedHeight / mConstrainedWidth;
      }

      x1 = *xNewPtr;
      y1 = slope * (*xNewPtr - x) + y;

      x2 = (*yNewPtr - y) / slope + x;
      y2 = *yNewPtr;

      // Chose the point that's closer to the user's actual selected point

      if(distance(x1, y1, x, y) < distance(x2, y2, x, y))
      {
         *xNewPtr = x1;
         *yNewPtr = y1;
      }
      else
      {
         *xNewPtr = x2;
         *yNewPtr = y2;
      }
   }
}

void FractalView::setZoomColor(int redValue, int greenValue, int blueValue)
{
   mZoomRed   = redValue;
   mZoomGreen = greenValue;
   mZoomBlue  = blueValue;
}

void FractalView::zoomInSettingsChanged()
{
   // If there is an active zoom rectangle, we need to remove it

   if(mState == STATE_ACTIVE)
   {
      mState    = STATE_READY;
      mX0 = mX1 = 0.0;
      mY0 = mY1 = 0.0;

      repaint();
   }
}

RowSupplier *FractalView::getRowSupplier(int *width, int *height)
{
   *width = *height = 0;
   RowSupplier *supplier = NULL;

   if(mImage)
   {
      QImageRowSupplier *q = 0;

      DNEW(q, QImageRowSupplier(mImage));

      *width   = q->getWidth();
      *height  = q->getHeight();
      supplier = q;
   }

   return(supplier);
}
