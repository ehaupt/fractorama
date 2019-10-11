// C/C++ Headers

#include <stdlib.h>
#include <string.h>

// Qt Headers

#include <qapplication.h>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include <qlayout.h>

// Local Headers

#include "antialiasdialog.h"

AntiAliasDialog::AntiAliasDialog(int antiAlias, QWidget *parent)
   : QDialog(parent, "AntiAliasDialog", TRUE)
{
   setCaption("Anti Alias Option");

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

   mBox = new QCheckBox("Generate tiff files antialiased", this, "mBox");

   if(antiAlias)
      mBox->setChecked(TRUE);
   else
      mBox->setChecked(FALSE);

   top->addWidget(mBox);
}

int AntiAliasDialog::getAntiAlias()
{
   return(mBox->isChecked());
}
