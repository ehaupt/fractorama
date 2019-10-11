#ifndef _GradientEditor_H_
#   define _GradientEditor_H_

#include <qdialog.h>

class QStringList;
class QPushButton;
class QSpinBox;
class QWidget;
class GWidget;
class QColor;
class QString;
class QLabel;

class GradientEditor : public QDialog
{
   Q_OBJECT

   public:
      GradientEditor(
         char *fractalFileName,
         QWidget *parent  = 0,
         const char *name = 0,
         bool modal       = FALSE,
         WFlags f         = 0
      );

      ~GradientEditor();

      void setCurrentColor(const QColor &theColor);
      void getCurrentColor(QColor &theColor);

      void getGradient(QString &theString);

      void handlePct(int theValue, int state);

      int loadFromStringList(QStringList &theList);

      void applyStep(int step);

   public slots:
      void colorSelected();
      void redChanged(int value);
      void greenChanged(int value);
      void blueChanged(int value);
      void pctChanged(int value);
      void darker();
      void lighter();
      void doClear();
      void doSpaceEvenly();
      void doSave();
      void doLoad();

   private:
      QString      mFractalFileName;
      QPushButton *mCurrentColor;
      QSpinBox    *mRed;
      QSpinBox    *mGreen;
      QSpinBox    *mBlue;
      QSpinBox    *mPct; 
      GWidget     *mGWidget;
};

#endif
