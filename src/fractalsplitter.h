#ifndef _FRACTAL_SPLITTER_H_
#   define _FRACTAL_SPLITTER_H_

#include <qsplitter.h>

class FractalView;
class QMultiLineEdit;

class FractalSplitter : public QSplitter
{
   Q_OBJECT

   public:
      FractalSplitter(QWidget *parent);
      ~FractalSplitter();
      QMultiLineEdit *getEdit();
      FractalView *getView();
      void setTopAndBottomSize(int top, int bottom);

   signals:
      void sizesChanged(int top, int bottom);

   protected:
      void timerEvent(QTimerEvent *e);

   private:
      int mTop;
      int mBottom;
      QMultiLineEdit *mEdit;
      FractalView    *mView;
};
#endif
