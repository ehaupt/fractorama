// Qt Headers

#include <qframe.h>
#include <qlayout.h>
#include <qfont.h>
#include <qmultilineedit.h>

// Local Headers

#include "fractalsplitter.h"
#include "fractalview.h"

FractalSplitter::FractalSplitter(
   QWidget *parent
) :
   QSplitter(QSplitter::Vertical, parent, "fractalsplitter"),
   mTop(0),
   mBottom(0),
   mEdit(0),
   mView(0)
{
   startTimer(1000);

   mEdit = new QMultiLineEdit(this, "mEdit");
   mEdit->setFont(QFont("courier"));
   mEdit->setWordWrap(QTextEdit::NoWrap);

   // Create "decorativeFrame" - so that our FractalView object
   // will have nice, shaded borders

   QFrame *decorativeFrame  = new QFrame(this, "decorativeFrame");
   decorativeFrame->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);

   QVBoxLayout *layout = new QVBoxLayout(
      decorativeFrame,
      decorativeFrame->lineWidth()
   );

   mView = new FractalView(decorativeFrame, "fractalview");
   layout->addWidget(mView,  0);
}

FractalSplitter::~FractalSplitter()
{
   // Nothing to do
}

QMultiLineEdit *FractalSplitter::getEdit()
{
   return(mEdit);
}

FractalView *FractalSplitter::getView()
{
   return(mView);
}

void FractalSplitter::setTopAndBottomSize(int top, int bottom)
{
   QValueList<int> sizes;

   sizes += top;
   sizes += bottom;

   setSizes(sizes);
}

void FractalSplitter::timerEvent(QTimerEvent *)
{
   QValueList<int> current = sizes();

   // This test should never fail

   if(current.count() == 2)
   {
      int currentTop    = current[0];
      int currentBottom = current[1];

      if(currentTop != mTop || currentBottom != mBottom)
      {
         // We seem to get a spurious set of sizes on startup (30, 30) -
         // weed this out by ensuring that the sum of the sizes is at
         // least 80% of the total height (valid sums will actually be
         // much close to 100% but err on the side of caution)

         if(currentTop + currentBottom > .8 * height())
         {
            mTop    = currentTop;
            mBottom = currentBottom;

            emit sizesChanged(mTop, mBottom);
         }
      }
   }
}
