// C/C++ Headers

#include <stdio.h>
#include <stdlib.h>

// Qt Headers

#include <qapplication.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qspinbox.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qlabel.h>
#include <qbrush.h>
#include <qimage.h>
#include <qregexp.h>
#include <qvaluelist.h>
#include <qfileinfo.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qdir.h>

// Local Headers

#include "gradienteditor.h"
#include "dmemory.h"

#define STATE_ENABLE    (0)
#define STATE_DISABLE   (1)
#define STATE_NO_CHANGE (2)

/************************************************************************** 
 * Local Class: PageUpPageDownSpinBox
 **************************************************************************/

class PageUpPageDownSpinBox : public QSpinBox
{
   public:
      PageUpPageDownSpinBox(
         QWidget *parent, int low, int high, int pageStep
      );

   protected:
      void keyReleaseEvent(QKeyEvent *e);

   private:
      int mPageStep;
};

PageUpPageDownSpinBox::PageUpPageDownSpinBox(
   QWidget *parent, int low, int high, int pageStep
) :
   QSpinBox(low, high, 1, parent),
   mPageStep(pageStep)
{
}

void PageUpPageDownSpinBox::keyReleaseEvent(QKeyEvent *e)
{
   if(e->key() == Qt::Key_PageUp)
   {
      int current = atoi(text().latin1());

      setValue(
         current + mPageStep <= maxValue() ? current + mPageStep : maxValue()
      );
   }
   else if(e->key() == Qt::Key_PageDown)
   {
      int current = atoi(text().latin1());

      setValue(
         current - mPageStep >= minValue() ? current - mPageStep : minValue()
      );
   }
   else
   {
      e->ignore();
   }
}

/************************************************************************** 
 * Local Struct: ColorEntry
 **************************************************************************/

#define TYPE_FIXED  (0)
#define TYPE_NORMAL (1)

struct ColorEntry
{
   ColorEntry(
      int red, int green, int blue, double percentage, int type
   );

   int    mRed;
   int    mGreen;
   int    mBlue;
   double mPercentage;
   int    mType;
};

ColorEntry::ColorEntry(
   int red, int green, int blue, double percentage, int type
) :
   mRed(red),
   mGreen(green),
   mBlue(blue),
   mPercentage(percentage),
   mType(type)
{
}

class GWidget : public QWidget
{
   public:
      GWidget(GradientEditor *editor);
      void updateSelected();
      int getXValue(double percentage);
      double getPercentage(int x);
      void findStartEnd(int *startPtr, int *endPtr);
      void getGradient(QString &theString);
      void doClear();
      void doSpaceEvenly();
      void moveSelected(int percentage);
      ColorEntry *addEntry(int r, int g, int b, double percentage);
      ~GWidget();

   protected:
      void paintEvent(QPaintEvent *);
      void mousePressEvent(QMouseEvent *e);
      void mouseMoveEvent(QMouseEvent *e);

   private:
      void sortEntries();
      void setSelected(ColorEntry *entry);

      GradientEditor *mEditor;
      ColorEntry **mEntries;
      int mNEntries;
      ColorEntry *mSelected;
      int mX;
      int mY;
      int mW;
      int mH;
      int mX1;
      int mY1;
      int mX2;
      int mY2;
      QImage mImage;
};

#define GWIDGET_MARGIN (10)
#define GWIDGET_HEIGHT (60)
#define GWIDGET_SIZE   (4)
#define GWIDGET_REMOVE (20)

GWidget::GWidget(GradientEditor *editor) :
   QWidget(editor),
   mEditor(editor),
   mEntries(0),
   mNEntries(0),
   mSelected(0),
   mX(0), mY(0), mW(0), mH(0),
   mX1(0), mY1(0), mX2(0), mY2(0),
   mImage(101, 1, 32)
{
   setMinimumHeight(110);
   setMaximumHeight(110);

   mX  = GWIDGET_MARGIN;
   mY  = GWIDGET_MARGIN;
   mH  = GWIDGET_HEIGHT;
   mX1 = mX;
   mY1 = mY2 = mY + mH + 2 * GWIDGET_MARGIN;

   mNEntries = 2;
   DNEW(mEntries, ColorEntry *[mNEntries]);

   DNEW(mEntries[0], ColorEntry(0, 0, 0, 0.0,   TYPE_FIXED));
   DNEW(mEntries[1], ColorEntry(0, 0, 0, 100.0, TYPE_FIXED));
}

GWidget::~GWidget()
{
   for(int i = 0; i < mNEntries; i ++)
      DDELETE(mEntries[i]);

   DADELETE(mEntries);
}

void GWidget::updateSelected()
{
   if(mSelected)
   {
      QColor theColor;

      mEditor->getCurrentColor(theColor);

      mSelected->mRed   = theColor.red();
      mSelected->mGreen = theColor.green();
      mSelected->mBlue  = theColor.blue();

      repaint(FALSE);
   }
}

int GWidget::getXValue(double percentage)
{
   return(
      mX1 + (int)(.01 * percentage * (mX2 - mX1) + 0.5)
   );
}

double GWidget::getPercentage(int x)
{
   double percentage = 100.0 * (double)(x - mX1) / (mX2 - mX1);

   if(percentage < 0.0)
      percentage = 0.0;

   else if(percentage >= 100.0)
      percentage = 100.0;

   return(percentage);
}

void GWidget::findStartEnd(int *startPtr, int *endPtr)
{
   int start = 0;

   while(mEntries[start + 1]->mPercentage == 0.0)
      start++;

   int end = mNEntries - 1;

   while(mEntries[end - 1]->mPercentage == 100.0)
      end--;

   *startPtr = start;
   *endPtr   = end;
}

void GWidget::getGradient(QString &theString)
{
   theString =
      "   colors\n"
      "   {\n"
      "      define\n"
      "      {\n";

   int start = 0;
   int end   = 0;

   findStartEnd(&start, &end);

   char buffer[255] = { '\0' };

   for(int i = start; i < end; i ++)
   {
      int startIndex = (int)(mEntries[i]->mPercentage     * 10.0 + 0.5);
      int endIndex   = (int)(mEntries[i + 1]->mPercentage * 10.0 + 0.5);

      if(i == start)
      {
         sprintf(
            buffer,
            "         gradient(%4d) { [%3d %3d %3d][%3d %3d %3d] }\n",
            (endIndex - startIndex) + 1,
            mEntries[i]->mRed,
            mEntries[i]->mGreen,
            mEntries[i]->mBlue,
            mEntries[i + 1]->mRed,
            mEntries[i + 1]->mGreen,
            mEntries[i + 1]->mBlue
         );
      }
      else
      {
         int gap = endIndex - startIndex;

         double dRed   = mEntries[i + 1]->mRed   - mEntries[i]->mRed;
         double dGreen = mEntries[i + 1]->mGreen - mEntries[i]->mGreen;
         double dBlue  = mEntries[i + 1]->mBlue  - mEntries[i]->mBlue;

         dRed   /= gap;
         dGreen /= gap;
         dBlue  /= gap;

         sprintf(
            buffer,
            "         gradient(%4d) { [%3d %3d %3d][%3d %3d %3d] }\n",
            gap,
            (int)(mEntries[i]->mRed   + dRed   + 0.5),
            (int)(mEntries[i]->mGreen + dGreen + 0.5),
            (int)(mEntries[i]->mBlue  + dBlue  + 0.5),
            mEntries[i + 1]->mRed,
            mEntries[i + 1]->mGreen,
            mEntries[i + 1]->mBlue
         );
      }

      theString += buffer;
   }

   theString +=
      "      }\n"
      "   }\n";
}

void GWidget::doClear()
{
   ColorEntry **newEntries = 0;

   DNEW(newEntries, ColorEntry *[2]);

   for(int i = 0, j = 0; i < mNEntries; i ++)
   {
      if(mEntries[i]->mType == TYPE_FIXED)
         newEntries[j++] = mEntries[i];
      else
         DDELETE(mEntries[i]);
   }

   delete [] mEntries;

   mNEntries = 2;
   mEntries  = newEntries;

   setSelected(0);

   repaint(FALSE);
}

void GWidget::doSpaceEvenly()
{
   int count = 0;
   int i     = 0;

   for(i = 0; i < mNEntries; i ++)
   {
      if(mEntries[i]->mPercentage > 0.0 && mEntries[i]->mPercentage < 100.0)
         count++;
   }

   if(count > 0)
   {
      double step  = 100.0 / (count + 1);
      double value = step;

      for(i = 0; i < mNEntries; i ++)
      {
         if(mEntries[i]->mPercentage > 0.0 &&
            mEntries[i]->mPercentage < 100.0)
         {
            mEntries[i]->mPercentage = value;

            if(mEntries[i] == mSelected)
            {
               mEditor->handlePct(
                  (int)(value + 0.5), STATE_NO_CHANGE
               );
            }

            value += step;

         }
      }

      repaint(FALSE);
   }
}

void GWidget::moveSelected(int percentage)
{
   mSelected->mPercentage = (double)percentage;
   repaint(FALSE);
}

ColorEntry *GWidget::addEntry(int r, int g, int b, double percentage)
{
   ColorEntry *entry = 0;

   DNEW(entry, ColorEntry(r, g, b, percentage, TYPE_NORMAL));

   ColorEntry *last = mEntries[mNEntries - 1];

   ColorEntry **newEntries = 0;

   DNEW(newEntries, ColorEntry *[mNEntries + 1]);

   for(int j = 0; j < mNEntries; j ++)
   {
      if(j + 1 == mNEntries)
         newEntries[j] = entry;
      else
         newEntries[j] = mEntries[j];
   }

   newEntries[mNEntries] = last;

   DADELETE(mEntries);
   mEntries = newEntries;
   mNEntries++;

   return(entry);
}

void GWidget::sortEntries()
{
   for(int i = 0; i < mNEntries - 1; i ++)
   {
      for(int j = i; j < mNEntries - 1; j ++)
      {
         if(mEntries[j]->mPercentage > mEntries[j + 1]->mPercentage)
         {
            ColorEntry *tmp = mEntries[j];
            mEntries[j]     = mEntries[j + 1];
            mEntries[j + 1] = tmp;
         }
      }
   }
}

void GWidget::setSelected(ColorEntry *entry)
{
   mSelected = entry;

   if(entry)
   {
      mEditor->handlePct((int)(entry->mPercentage + 0.5), STATE_ENABLE);
   }
   else
   {
      mEditor->handlePct(0, STATE_DISABLE);
   }
}

void GWidget::paintEvent(QPaintEvent *)
{
   QPixmap pm(size());
   pm.fill(backgroundColor());
   mImage.fill(0);

   QPainter p;
   p.begin(&pm);

   sortEntries();

   int start = 0;
   int end   = 0;
   int i     = 0;

   findStartEnd(&start, &end);

   for(i = start; i < end; i ++)
   {
      int thisOffset = (int)(mEntries[i]->mPercentage + 0.5);
      int nextOffset = (int)(mEntries[i + 1]->mPercentage + 0.5);

      double d = nextOffset - thisOffset;

      if(d > 0.0)
      {
         double red   = mEntries[i]->mRed;
         double green = mEntries[i]->mGreen;
         double blue  = mEntries[i]->mBlue;

         double rstep = (mEntries[i + 1]->mRed   - red)   / d;
         double gstep = (mEntries[i + 1]->mGreen - green) / d;
         double bstep = (mEntries[i + 1]->mBlue  - blue)  / d;

         for(int j = thisOffset; j <= nextOffset; j ++)
         {
            QColor theColor(
               (int)(red   + 0.5),
               (int)(green + 0.5),
               (int)(blue  + 0.5)
            );

            mImage.setPixel(j, 0, theColor.rgb());

            red   += rstep;
            green += gstep;
            blue  += bstep;
         }
      }
   }

   // Reset these each time so our widget can be
   // gracefully resized

   mW  = width() - 2 * GWIDGET_MARGIN;
   mX2 = mX + mW;

   p.drawImage(QRect(mX, mY, mW, mH), mImage);

   p.drawRect(mX, mY, mW, mH);

   p.drawLine(mX1, mY1, mX2, mY2);

   for(i = start; i <= end; i ++)
   {
      int xValue = getXValue(mEntries[i]->mPercentage);

      p.fillRect(
         xValue - GWIDGET_SIZE,
         mY1    - GWIDGET_SIZE,
         2 * GWIDGET_SIZE,
         2 * GWIDGET_SIZE,
         QBrush(
            QColor(
               mEntries[i]->mRed,
               mEntries[i]->mGreen,
               mEntries[i]->mBlue
            )
         )
      );

      // If this entry's selected, highlight it ...

      if(mSelected == mEntries[i])
      {
         p.drawRect(
            xValue - GWIDGET_SIZE - 3,
            mY1    - GWIDGET_SIZE - 3,
            2 * (GWIDGET_SIZE + 3),
            2 * (GWIDGET_SIZE + 3)
         );
      }
   }

   p.end();
   bitBlt(this, 0, 0, &pm);
}

void GWidget::mousePressEvent(QMouseEvent *e)
{
   // Are we within 'y' range of our line?

   int yDelta = e->y() - mY1;

   if(yDelta < 0)
      yDelta = -yDelta;

   if(yDelta > GWIDGET_SIZE)
   {
      // We're out of range, clear our current selection

      if(mSelected)
      {
         setSelected(0);
         repaint(FALSE);
         return;
      }
   }

   // Ok, we're within 'y' range ... now check 'x'

   if(e->x() >= mX1 - GWIDGET_SIZE && e->x() <= mX2 + GWIDGET_SIZE)
   {
      // Ok, two possibilities ... we're selecting an existing point
      // or we're adding a new one

      for(int i = 0; i < mNEntries; i ++)
      {
         if(mEntries[i]->mType != TYPE_FIXED)
         {
            int xValue = getXValue(mEntries[i]->mPercentage);

            if(e->x() >= xValue - GWIDGET_SIZE &&
               e->x() <= xValue + GWIDGET_SIZE)
            {
               // We've selected an existing point

               setSelected(mEntries[i]);

               // Make our color square reflect this entry's color ...

               QColor entryColor(
                  mEntries[i]->mRed,
                  mEntries[i]->mGreen,
                  mEntries[i]->mBlue
               );

               mEditor->setCurrentColor(entryColor);

               repaint(FALSE);

               return;
            }
         }
      }

      // Ok, if we're here ... we're adding a new entry, we need
      // to grab the current color and work out our percentage
      // to create our new entry

      QColor theColor;

      mEditor->getCurrentColor(theColor);

      setSelected(
         addEntry(
            theColor.red(),
            theColor.green(),
            theColor.blue(),
            getPercentage(e->x())
         )
      );

      repaint(FALSE);
   }
}

void GWidget::mouseMoveEvent(QMouseEvent *e)
{
   if(mSelected)
   {
      // Are we removing this entry?

      if(e->y() < mY1 - GWIDGET_REMOVE || e->y() > mY1 + GWIDGET_REMOVE)
      {
         ColorEntry **newEntries = 0;

         DNEW(newEntries, ColorEntry *[mNEntries - 1]);
 
         for(int i = 0, j = 0; i < mNEntries; i ++)
         {
            if(mEntries[i] != mSelected)
            {
               newEntries[j++] = mEntries[i];
            }
         }

         DADELETE(mEntries);
         mEntries = newEntries;
         mNEntries--;

         setSelected(0);

         repaint(FALSE);
      }
      else
      {
         // Move the entry

         mSelected->mPercentage = getPercentage(e->x());

         mEditor->handlePct(
            (int)(mSelected->mPercentage + 0.5), STATE_NO_CHANGE
         );

         repaint(FALSE);
      }
   }
}

GradientEditor::GradientEditor(
   char *fractalFileName,
   QWidget *parent,
   const char *name,
   bool modal,
   WFlags f
) :
   QDialog(parent, name, modal, f),
  mFractalFileName(fractalFileName),
  mCurrentColor(0),
  mRed(0),
  mGreen(0),
  mBlue(0),
  mPct(0),
  mGWidget(0)
{
   QVBoxLayout *vertical = new QVBoxLayout(this);

   QHBoxLayout *top = new QHBoxLayout(vertical);

   QGridLayout *colorsLayout = new QGridLayout(top, 8, 32);

   int colors[4] = { 0, 85, 170, 255 };
   int rFactor   = 16;
   int gFactor   = 4;
   int bFactor   = 1;

   for(int i = 0, k = 0; i < 4; i ++)
   {
      for(int j = 0; j < 16; j ++, k ++)
      {
         QPushButton *b = new QPushButton(this);

         b->setMaximumWidth(25);
         b->setMaximumHeight(25);

         QColor theColor(
            colors[(k / rFactor) % 4],
            colors[(k / gFactor) % 4],
            colors[(k / bFactor) % 4]
         );

         b->setPaletteBackgroundColor(theColor);

         colorsLayout->addWidget(b, i, j);

         QObject::connect(
            b, SIGNAL(pressed()), this, SLOT(colorSelected())
         );
      }
   }

   top->addSpacing(20);

   mCurrentColor = new QPushButton(this);

   mCurrentColor->setMaximumWidth(60);
   mCurrentColor->setMaximumHeight(60);
   mCurrentColor->setMinimumWidth(60);
   mCurrentColor->setMinimumHeight(60);

   mCurrentColor->setPaletteBackgroundColor(QColor(0, 0, 0));

   QPushButton *darker  = new QPushButton(this);
   QPushButton *lighter = new QPushButton(this);

   darker->setMaximumWidth(25);
   darker->setMaximumHeight(25);
   darker->setPaletteBackgroundColor(QColor(0, 0, 0));

   QObject::connect(
      darker, SIGNAL(clicked()), this, SLOT(darker())
   );

   lighter->setMaximumWidth(25);
   lighter->setMaximumHeight(25);
   lighter->setPaletteBackgroundColor(QColor(255, 255, 255));

   QObject::connect(
      lighter, SIGNAL(clicked()), this, SLOT(lighter())
   );

   QVBoxLayout *v = new QVBoxLayout(top);

   v->addWidget(mCurrentColor);

   QHBoxLayout *h = new QHBoxLayout(v);

   h->addWidget(darker);
   h->addWidget(lighter);

   top->addSpacing(20);

   QGridLayout *valueLayout = new QGridLayout(top, 4, 2);

   valueLayout->addWidget(new QLabel("Red",   this),  0, 0);
   valueLayout->addWidget(new QLabel("Green", this),  1, 0);
   valueLayout->addWidget(new QLabel("Blue",  this),  2, 0);
   valueLayout->addWidget(new QLabel("Pct",   this),  3, 0);

   mRed   = new PageUpPageDownSpinBox(this, 0, 255, 10);
   mGreen = new PageUpPageDownSpinBox(this, 0, 255, 10);
   mBlue  = new PageUpPageDownSpinBox(this, 0, 255, 10);
   mPct   = new PageUpPageDownSpinBox(this, 0, 100, 5);

   QObject::connect(
      mRed, SIGNAL(valueChanged(int)), this, SLOT(redChanged(int))
   );

   QObject::connect(
      mGreen, SIGNAL(valueChanged(int)), this, SLOT(greenChanged(int))
   );

   QObject::connect(
      mBlue, SIGNAL(valueChanged(int)), this, SLOT(blueChanged(int))
   );

   QObject::connect(
      mPct, SIGNAL(valueChanged(int)), this, SLOT(pctChanged(int))
   );

   valueLayout->addWidget(mRed,   0, 1);
   valueLayout->addWidget(mGreen, 1, 1);
   valueLayout->addWidget(mBlue,  2, 1);
   valueLayout->addWidget(mPct,   3, 1);

   handlePct(0, STATE_DISABLE);

   vertical->addWidget(mGWidget = new GWidget(this));
   vertical->addSpacing(20);

   QHBoxLayout *buttonLayout = new QHBoxLayout(vertical);

   QPushButton *ok = new QPushButton("Ok", this);

   QObject::connect(
      ok, SIGNAL(clicked()), this, SLOT(accept())
   );

   QPushButton *cancel = new QPushButton("Cancel", this);

   QObject::connect(
      cancel, SIGNAL(clicked()), this, SLOT(reject())
   );

   QPushButton *clear = new QPushButton("Clear", this);

   QObject::connect(
      clear, SIGNAL(clicked()), this, SLOT(doClear())
   );

   QPushButton *spaceEvenly = new QPushButton("Space Evenly", this);

   QObject::connect(
      spaceEvenly, SIGNAL(clicked()), this, SLOT(doSpaceEvenly())
   );

   QPushButton *save = new QPushButton("Save", this);

   QObject::connect(
      save, SIGNAL(clicked()), this, SLOT(doSave())
   );

   QPushButton *load = new QPushButton("Load", this);

   QObject::connect(
      load, SIGNAL(clicked()), this, SLOT(doLoad())
   );

   buttonLayout->addSpacing(20);
   buttonLayout->addWidget(ok);
   buttonLayout->addSpacing(20);
   buttonLayout->addWidget(cancel);
   buttonLayout->addSpacing(20);
   buttonLayout->addWidget(clear);
   buttonLayout->addSpacing(20);
   buttonLayout->addWidget(spaceEvenly);
   buttonLayout->addSpacing(20);
   buttonLayout->addWidget(save);
   buttonLayout->addSpacing(20);
   buttonLayout->addWidget(load);

   vertical->addSpacing(20);
}

void GradientEditor::setCurrentColor(const QColor &theColor)
{
   mCurrentColor->setPaletteBackgroundColor(theColor);

   mRed->setValue(theColor.red());
   mGreen->setValue(theColor.green());
   mBlue->setValue(theColor.blue());
}

void GradientEditor::getCurrentColor(QColor &theColor)
{
   const QColor &c = mCurrentColor->paletteBackgroundColor();

   theColor.setRgb(c.red(), c.green(), c.blue());
}

void GradientEditor::getGradient(QString &theString)
{
   mGWidget->getGradient(theString);
}

void GradientEditor::handlePct(int theValue, int state)
{
   mPct->blockSignals(TRUE);
   mPct->setValue(theValue);
   mPct->blockSignals(FALSE);

   switch(state)
   {
      case STATE_ENABLE : mPct->setEnabled(TRUE);  break;
      case STATE_DISABLE: mPct->setEnabled(FALSE); break;
   }
}

struct LoadFromStringListEntry { int values[7]; };

typedef QValueList<LoadFromStringListEntry> EntryList;

int GradientEditor::loadFromStringList(QStringList &theList)
{
   EntryList entryList;

   QRegExp gradientRegex(
      "\\s*gradient\\s*\\(\\s*(\\d+)"
      "\\s*\\)\\s*\\{\\s*\\[\\s*"
      "(\\d+)\\s*(\\d+)\\s*(\\d+)\\s*"
      "\\]\\s*\\[\\s*(\\d+)\\s*(\\d+)"
      "\\s*(\\d+)\\s*\\]\\s*\\}"
   );

   int total               = 0;
   QStringList::Iterator i = theList.begin();

   while(i != theList.end())
   {
      QString line = *i;

      if(gradientRegex.search(line) != -1)
      {
         LoadFromStringListEntry theEntry;

         for(int j = 0; j < 7; j ++)
            theEntry.values[j] = atoi(gradientRegex.cap(j + 1));

         total += theEntry.values[0];

         entryList += theEntry; 
      }

      i++;
   }

   if(total > 0)
   {
      mGWidget->doClear();

      EntryList::Iterator theIterator = entryList.begin();
      int sum                         = 0;

      total--;

      while(theIterator != entryList.end())
      {
         LoadFromStringListEntry theEntry = *theIterator;

         if(sum == 0)
         {
            mGWidget->addEntry(
               theEntry.values[1],
               theEntry.values[2],
               theEntry.values[3],
               0.0
            );

            theEntry.values[0]--;
         }

         sum += theEntry.values[0];

         mGWidget->addEntry(
            theEntry.values[4],
            theEntry.values[5],
            theEntry.values[6],
            100.0 * sum / total
         );

         theIterator++;
      }

      mGWidget->repaint(FALSE);
   }

   return(total > 0);
}

void GradientEditor::colorSelected()
{
   QPushButton *b  = (QPushButton *)sender();
   const QColor &c = b->paletteBackgroundColor();

   setCurrentColor(c);

   mGWidget->updateSelected();
}

void GradientEditor::redChanged(int value)
{
   const QColor &c = mCurrentColor->paletteBackgroundColor();

   mCurrentColor->setPaletteBackgroundColor(
      QColor(value, c.green(), c.blue())
   );

   mGWidget->updateSelected();
}

void GradientEditor::greenChanged(int value)
{
   const QColor &c = mCurrentColor->paletteBackgroundColor();

   mCurrentColor->setPaletteBackgroundColor(
      QColor(c.red(), value, c.blue())
   );

   mGWidget->updateSelected();
}

void GradientEditor::blueChanged(int value)
{
   const QColor &c = mCurrentColor->paletteBackgroundColor();

   mCurrentColor->setPaletteBackgroundColor(
      QColor(c.red(), c.green(), value)
   );

   mGWidget->updateSelected();
}

void GradientEditor::pctChanged(int value)
{
   mGWidget->moveSelected(value);
}

void GradientEditor::applyStep(int step)
{
   const QColor &c = mCurrentColor->paletteBackgroundColor();

   int r = c.red()   + step;
   int g = c.green() + step;
   int b = c.blue()  + step;

   r = (r < 0 ? 0 : r > 255 ? 255 : r);
   g = (g < 0 ? 0 : g > 255 ? 255 : g);
   b = (b < 0 ? 0 : b > 255 ? 255 : b);

   setCurrentColor(QColor(r, g, b));

   mGWidget->updateSelected();
}

void GradientEditor::darker()
{
   applyStep(-10);
}

void GradientEditor::lighter()
{
   applyStep(10);
}

void GradientEditor::doClear()
{
   mGWidget->doClear();
}

void GradientEditor::doSpaceEvenly()
{
   mGWidget->doSpaceEvenly();
}

#define GRADIENT_EXTENSION ".kld"

void GradientEditor::doSave()
{
   QFileInfo fileInfo = mFractalFileName;
   QDir theDir        = fileInfo.dir();
   QString saveName   = fileInfo.baseName(TRUE) + GRADIENT_EXTENSION;

   fileInfo = QFileInfo(theDir, saveName);
   saveName = fileInfo.filePath();

   while(1)
   {
      QString theString = QFileDialog::getSaveFileName(
         saveName, "*"GRADIENT_EXTENSION
      );

      if(theString.isEmpty())
      {
         // User cancelled the save

         break;
      }

      // If the supplied filename doesn't end in GRADIENT_EXTENSION,
      // add GRADIENT_EXTENSION

      int length = theString.length();
      int index  = theString.findRev(GRADIENT_EXTENSION, -1, FALSE);

      if(index == -1 || index != (int)(length - strlen(GRADIENT_EXTENSION)))
         theString.append(GRADIENT_EXTENSION);

      // See if the user is attempting to overwrite an existing file

      int saveFile = true;
      QFile theFile(theString);

      if(theFile.exists())
      {
         int response = QMessageBox::information(
            this,
            "SaveText",
            "Overwrite existing file?",
            "&Yes", "&No", "&Cancel",
            0, 2
         );

         if(response == 1)
            saveFile = false;

         else if(response == 2)
            break;
      }

      if(saveFile)
      {
         QFile dest(theString);

         if(!dest.open(IO_WriteOnly))
         {
            QString error("Error writing file: [");
            error.append(theString);
            error.append("]");

            QMessageBox::message("Error", error);
         }
         else
         {
            QString theGradient;

            mGWidget->getGradient(theGradient);

            dest.writeBlock(theGradient.latin1(), theGradient.length());
            dest.close();
         }

         break;
      }
   }
}

void GradientEditor::doLoad()
{
   QFileInfo fileInfo = mFractalFileName;

   QString theString = QFileDialog::getOpenFileName(
      fileInfo.dirPath(), "*"GRADIENT_EXTENSION, this
   );

   if(theString.isEmpty())
      return;

   QFile theFile(theString);

   if(!theFile.open(IO_ReadOnly))
   {
      QString error("Unable to open file: [" + theString + "]");
      QMessageBox::message("Error", error);

      return;
   }

   // Ok, read in the lines of the file

   QStringList theList;

   while(1)
   {
      QString line;

      if(theFile.readLine(line, 4096) == -1)
         break;

      theList += line;
   }

   if(!loadFromStringList(theList))
   {
      QString error("Error reading gradient from: [" + theString + "]");
      QMessageBox::message("Error", error);
   }
}

GradientEditor::~GradientEditor()
{
}

#if 0

int main(int argc, char **argv)
{
   QApplication theApplication(argc, argv);
   GradientEditor theObject(NULL, "theObject", TRUE);

   int returnValue = theObject.exec();

   QString s;

   theObject.getGradient(s);

   printf("%s\n", s.latin1());

   return(returnValue);
}

#endif
