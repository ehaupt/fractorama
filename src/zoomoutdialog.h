#ifndef _ZoomOutDialog_H_
#   define _ZoomOutDialog_H_

#include <qdialog.h>

class QWidget;
class QLineEdit;

class ZoomOutDialog : public QDialog
{
   Q_OBJECT

   public:
      ZoomOutDialog(double scaleFactor, QWidget *parent = 0);
      double getScaleFactor();

   private:
      void setScaleFactor(QLineEdit *edit, double scaleFactor);

      QLineEdit *mEdit;

   protected slots:
      void done(int);
};

#endif
