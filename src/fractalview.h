#ifndef _FRACTAL_VIEW_H_
#define _FRACTAL_VIEW_H_

#include <qscrollview.h>
#include <qdatetime.h>

class QPixmap;
class Fractal;
class FractalObserver;
class StateSupplier;
class ApplicationWindow;
class RowSupplier;

class FractalView : public QScrollView
{
   public:
      FractalView(
         QWidget *parent = 0,
         const char * name = 0,
         WFlags f = 0
      );

      ~FractalView();

      void newFractal(
         Fractal *theFractal,
         FractalObserver *observer,
         StateSupplier *supplier
      );

      void stop();

      int getZoomCoordinates(
         double *x0Ptr,
         double *y0Ptr,
         double *x1Ptr,
         double *y1Ptr
      );

      void setZoomColor(int redValue, int greenValue, int blueValue);

      void zoomInSettingsChanged();

      RowSupplier *getRowSupplier(int *width, int *height);

   protected:
      virtual void drawContentsOffset(
         QPainter *,
         int ox, int oy,
         int cx, int cy,
         int cw, int ch
      );

      virtual void viewportPaintEvent(QPaintEvent*);
      virtual void paintEvent(QPaintEvent *);
      virtual void viewportMousePressEvent(QMouseEvent *);
      virtual void viewportMouseMoveEvent(QMouseEvent *);
      virtual void viewportMouseReleaseEvent(QMouseEvent *);
      virtual void keyReleaseEvent(QKeyEvent *e);

   private:

      double clipX(double x, double offset = 0.0) const;
      double clipY(double y, double offset = 0.0) const;

      void setConstraints();

      void applyConstraints(
         double *xNewPtr, double *yNewPtr,
         double x, double y
      );

      enum
      {
         STATE_INITIAL,
         STATE_READY,
         STATE_ACTIVE,
         STATE_RESIZE_LT,
         STATE_RESIZE_CT,
         STATE_RESIZE_RT,
         STATE_RESIZE_LC,
         STATE_RESIZE_RC,
         STATE_RESIZE_LB,
         STATE_RESIZE_CB,
         STATE_RESIZE_RB,
         STATE_MOVE
      };

      enum { RECT_SIZE = 6 };

      QPixmap *mPixmap;
      QImage  *mImage;
      int mStopped;
      int mState;
      double mX0, mY0, mX1, mY1;
      double mXCurrent, mYCurrent;

      int mWidth, mHeight;
      StateSupplier *mSupplier;
      FractalObserver *mObserver;

      int mZoomRed, mZoomGreen, mZoomBlue;
      int mConstrained;
      double mConstrainedWidth;
      double mConstrainedHeight;
      int mExpectingMousePress;
};

#endif // _FRACTAL_VIEW_H_
