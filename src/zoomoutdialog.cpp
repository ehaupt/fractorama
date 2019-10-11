// C/C++ Headers

#include <iostream>
#include <stdlib.h>
#include <string.h>

using std::cout;
using std::endl;

// Qt Headers

#include <qapplication.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qlayout.h>

// Local Headers

#include "zoomoutdialog.h"

ZoomOutDialog::ZoomOutDialog(double scaleFactor, QWidget *parent)
   : QDialog(parent, "ZoomOutDialog", TRUE)
{
   setCaption("Zoom Out Options");

   QBoxLayout *layout = new QVBoxLayout(this, QBoxLayout::Down);
   layout->setMargin(5);
   layout->setSpacing(5);

   QBoxLayout *top = new QHBoxLayout(layout);
   layout->addSpacing(5);

   QBoxLayout *bottom = new QHBoxLayout(layout);
   top->addSpacing(5);

   // Create our various widgets ...

   QPushButton *ok     = new QPushButton("OK",     this, "ok");
   QPushButton *cancel = new QPushButton("Cancel", this, "cancel");

   bottom->addStretch(1);
   bottom->addWidget(ok);
   bottom->addStretch(1);
   bottom->addWidget(cancel);
   bottom->addStretch(1);

   connect(ok,     SIGNAL(clicked()), this, SLOT(accept()));
   connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));

   mEdit = new QLineEdit(this, "edit");
   setScaleFactor(mEdit, scaleFactor);

   top->addWidget(
      new QLabel("Please enter your zoom factor:", this, "prompt")
   );

   top->addWidget(mEdit);
}

double ZoomOutDialog::getScaleFactor()
{
   // It is assumed that this method won't be called except after the
   // dialog is dismissed by hitting 'ok', only via that path is this
   // method guaranteed to return a valid scale factor value

   return(strtod(mEdit->text().latin1(), NULL));
}

void ZoomOutDialog::setScaleFactor(QLineEdit *edit, double scaleFactor)
{
   QString text;
   text.sprintf("%.10f", scaleFactor);
   edit->setText(text);
}

void ZoomOutDialog::done(int value)
{
   if(value == 1)
   {
      // User pressed 'ok', ensure the supplied value for
      // scale factor is valid

      char *ptr     = NULL;
      double factor = strtod(mEdit->text().latin1(), &ptr);

      if(factor == 0.0 || ptr == NULL || *ptr != '\0')
      {
         QMessageBox::warning(
            this,
            "Invalid Scale Factor",
            "The scale factor must be a valid real number and must not be zero",
            QMessageBox::Ok, 0
         );

         // Put focus back on our QLineEdit widget

         mEdit->setFocus();

         return;
      }
   }

   // If we're here, the user either hit 'cancel' (in which case we don't
   // care whether or not the scale factor was valid) or hit 'ok' and the
   // scale factor was valid

   QDialog::done(value);
}

#if 0
int main(int argc, char **argv)
{
   QApplication theApplication(argc, argv);
   ZoomOutDialog theObject(1.0);

   if(theObject.exec())
   {
      // User pressed 'ok'

      cout << "scaleFactor : [" <<
         theObject.getScaleFactor() << "]" << endl;
   }

   return(0);
}
#endif
