// C/C++ Headers

#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

using std::cout;
using std::endl;

// Qt Headers

#include <qapplication.h>
#include <qpushbutton.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qlineedit.h>
#include <qvalidator.h>
#include <qmessagebox.h>
#include <qlayout.h>

// Local Headers

#include "zoomindialog.h"

ZoomInDialog::ZoomInDialog(
   ZoomInDialog::WidthOption widthOption,
   int userWidth,
   ZoomInDialog::HeightOption heightOption,
   int userHeight,
   QWidget *parent
) :
   QDialog(parent, "ZoomInDialog", TRUE),
   mWidthEdit(0),
   mHeightEdit(0),
   mWidthOption(widthOption),
   mHeightOption(heightOption)
{
   setCaption("Zoom In Options");

   QBoxLayout *layout = new QVBoxLayout(this, QBoxLayout::Down);
   layout->setMargin(5);
   layout->setSpacing(5);

   QBoxLayout *top    = new QHBoxLayout(layout);
   QBoxLayout *middle = new QHBoxLayout(layout);
   QBoxLayout *bottom = new QHBoxLayout(layout);

   // Create our ok/cancel buttons and wire up their signals ...

   QPushButton *ok     = new QPushButton("OK",     this, "ok");
   QPushButton *cancel = new QPushButton("Cancel", this, "cancel");

   QObject::connect(ok,     SIGNAL(clicked()), this, SLOT(accept()));
   QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));

   // Insert our ok/cancel buttons into our 'bottom' layout

   bottom->setMargin(5);
   bottom->addStretch(1);
   bottom->addWidget(ok);
   bottom->addStretch(1);
   bottom->addWidget(cancel);
   bottom->addStretch(1);

   // Now our width options

   QButtonGroup *widthGroup =
      new QButtonGroup("Width Option", this, "widthGroup");

   QRadioButton *widthUnspecified =
      new QRadioButton(
         "Unspecified",
         widthGroup,
         "widthUnspecified"
   );

   QRadioButton *widthParent =
      new QRadioButton(
         "Use parent fractal's width",
         widthGroup,
         "widthParent"
   );

   QRadioButton *widthUser =
      new QRadioButton(
         "User specified width",
         widthGroup,
         "widthUser"
   );

   mWidthEdit = new QLineEdit(widthGroup, "mWidthEdit");
   setField(userWidth, mWidthEdit);

   mWidthEdit->setValidator(
      new QIntValidator(
         1, INT_MAX, mWidthEdit, "mWidthEditValidator")
   );

   QBoxLayout *widthLayout = new QVBoxLayout(widthGroup);
   widthLayout->setSpacing(15);
   widthLayout->setMargin(15);
   widthLayout->addSpacing(15);

   QBoxLayout *w1 = new QHBoxLayout(widthLayout);
   w1->addWidget(widthUnspecified);

   QBoxLayout *w2 = new QHBoxLayout(widthLayout);
   w2->addWidget(widthParent);

   QBoxLayout *w3 = new QHBoxLayout(widthLayout);
   w3->addWidget(widthUser);
   w3->addStretch(1);
   w3->addWidget(mWidthEdit);
   w3->addStretch(1);

   // Check the appropriate option

   switch(mWidthOption)
   {
      case UNSPECIFIED_WIDTH:
      {
         widthUnspecified->setChecked(TRUE);
         mWidthEdit->setEnabled(FALSE);
      }
      break;

      case USE_PARENT_WIDTH:
      {
         widthParent->setChecked(TRUE);
         mWidthEdit->setEnabled(FALSE);
      }
      break;

      case USER_SPECIFIED_WIDTH:
      {
         widthUser->setChecked(TRUE);
         mWidthEdit->setEnabled(TRUE);
      }
      break;
   }

   QObject::connect(
      widthGroup,
      SIGNAL(clicked(int)),
      this,
      SLOT(slotWidthOptionChanged(int))
   );

   top->addWidget(widthGroup);

   // Now our height options

   QButtonGroup *heightGroup =
      new QButtonGroup("Height Option", this, "heightGroup");

   QRadioButton *heightUnspecified =
      new QRadioButton(
         "Unspecified",
         heightGroup,
         "heightUnspecified"
   );

   QRadioButton *heightParent =
      new QRadioButton(
         "Use parent fractal's height",
         heightGroup,
         "heightParent"
   );

   QRadioButton *heightUser =
      new QRadioButton(
         "User specified height",
         heightGroup,
         "heightUser"
   );

   mHeightEdit = new QLineEdit(heightGroup, "mHeightEdit");
   setField(userHeight, mHeightEdit);

   mHeightEdit->setValidator(
      new QIntValidator(
         1, INT_MAX, mHeightEdit, "mHeightEditValidator")
   );

   QBoxLayout *heightLayout = new QVBoxLayout(heightGroup);
   heightLayout->setSpacing(15);
   heightLayout->setMargin(15);
   heightLayout->addSpacing(15);

   QBoxLayout *h1 = new QHBoxLayout(heightLayout);
   h1->addWidget(heightUnspecified);

   QBoxLayout *h2 = new QHBoxLayout(heightLayout);
   h2->addWidget(heightParent);

   QBoxLayout *h3 = new QHBoxLayout(heightLayout);
   h3->addWidget(heightUser);
   h3->addStretch(1);
   h3->addStretch(1);
   h3->addWidget(mHeightEdit);
   h3->addStretch(1);
   h3->addStretch(1);

   // Check the appropriate option

   switch(mHeightOption)
   {
      case UNSPECIFIED_HEIGHT:
      {
         heightUnspecified->setChecked(TRUE);
         mHeightEdit->setEnabled(FALSE);
      }
      break;

      case USE_PARENT_HEIGHT:
      {
         heightParent->setChecked(TRUE);
         mHeightEdit->setEnabled(FALSE);
      }
      break;

      case USER_SPECIFIED_HEIGHT:
      {
         heightUser->setChecked(TRUE);
         mHeightEdit->setEnabled(TRUE);
      }
      break;
   }

   QObject::connect(
      heightGroup,
      SIGNAL(clicked(int)),
      this,
      SLOT(slotHeightOptionChanged(int))
   );

   middle->addWidget(heightGroup);
}

int ZoomInDialog::getUserSpecifiedWidth()
{
   return(atoi(mWidthEdit->text().latin1()));
}

int ZoomInDialog::getUserSpecifiedHeight()
{
   return(atoi(mHeightEdit->text().latin1()));
}

ZoomInDialog::WidthOption ZoomInDialog::getWidthOption()
{
   return(mWidthOption);
}

ZoomInDialog::HeightOption ZoomInDialog::getHeightOption()
{
   return(mHeightOption);
}

void ZoomInDialog::setField(int value, QLineEdit *field)
{
   QString text;
   text.sprintf("%d", value);
   field->setText(text);
}

void ZoomInDialog::slotWidthOptionChanged(int which)
{
   mWidthOption = (WidthOption)which;

   switch(mWidthOption)
   {
      case UNSPECIFIED_WIDTH:
      {
         mWidthEdit->setEnabled(FALSE);
      }
      break;

      case USE_PARENT_WIDTH:
      {
         mWidthEdit->setEnabled(FALSE);
      }
      break;

      case USER_SPECIFIED_WIDTH:
      {
         mWidthEdit->setEnabled(TRUE);
      }
      break;
   }
}

void ZoomInDialog::slotHeightOptionChanged(int which)
{
   mHeightOption = (HeightOption)which;

   switch(mHeightOption)
   {
      case UNSPECIFIED_HEIGHT:
      {
         mHeightEdit->setEnabled(FALSE);
      }
      break;

      case USE_PARENT_HEIGHT:
      {
         mHeightEdit->setEnabled(FALSE);
      }
      break;

      case USER_SPECIFIED_HEIGHT:
      {
         mHeightEdit->setEnabled(TRUE);
      }
      break;
   }
}

void ZoomInDialog::done(int value)
{
   if(value == 1)
   {
      // User pressed 'ok', ensure the supplied values for
      // width and height were acceptable

      int badWidth = (mWidthOption == USER_SPECIFIED_WIDTH &&
         getUserSpecifiedWidth() <= 0);

      int badHeight = (mHeightOption == USER_SPECIFIED_HEIGHT &&
         getUserSpecifiedHeight() <= 0);

      if(badWidth || badHeight)
      {
         char *title       = NULL;
         char *text        = NULL;
         QLineEdit *target = NULL;

         if(badWidth)
         {
            target = mWidthEdit;

            if(badHeight)
            {
               title = "Invalid Width and Height";
               text  =
                  "User supplied width and height must be positive integers";
            }
            else
            {
               title = "Invalid Width";
               text  = "User supplied width must be a positive integer";
            }
         }
         else
         {
            target = mHeightEdit;
            title  = "Invalid Height";
            text   = "User supplied height must be a positive integer";
         }

         QMessageBox::warning(this, title, text, QMessageBox::Ok, 0);

         // Put focus back on the offender

         target->setFocus();

         return;                                   
      }
   }

   // If we're here, either the user pressed escape or the values were ok

   QDialog::done(value);
}

const char *ZoomInDialog::toString(ZoomInDialog::WidthOption option)
{
   char *s = NULL;

   switch(option)
   {
      case UNSPECIFIED_WIDTH   : s = "unspecified_width";    break;
      case USE_PARENT_WIDTH    : s = "use_parent_width";     break;
      case USER_SPECIFIED_WIDTH: s = "user_specified_width"; break;
   }

   return(s);
}

const char *ZoomInDialog::toString(ZoomInDialog::HeightOption option)
{
   char *s = NULL;

   switch(option)
   {
      case UNSPECIFIED_HEIGHT   : s = "unspecified_height";    break;
      case USE_PARENT_HEIGHT    : s = "use_parent_height";     break;
      case USER_SPECIFIED_HEIGHT: s = "user_specified_height"; break;
   }

   return(s);
}

ZoomInDialog::WidthOption ZoomInDialog::widthOptionFromString(const char *s)
{
   if(strcmp(s, toString(USE_PARENT_WIDTH)) == 0)
      return(USE_PARENT_WIDTH);

   if(strcmp(s, toString(USER_SPECIFIED_WIDTH)) == 0)
      return(USER_SPECIFIED_WIDTH);

   return(UNSPECIFIED_WIDTH);
}

ZoomInDialog::HeightOption ZoomInDialog::heightOptionFromString(const char *s)
{
   if(strcmp(s, toString(USE_PARENT_HEIGHT)) == 0)
      return(USE_PARENT_HEIGHT);

   if(strcmp(s, toString(USER_SPECIFIED_HEIGHT)) == 0)
      return(USER_SPECIFIED_HEIGHT);

   return(UNSPECIFIED_HEIGHT);
}

/*****************************************************************************
 * For Unit Testing
 *****************************************************************************/

#if 0

int main(int argc, char **argv)
{
   QApplication theApplication(argc, argv);

   ZoomInDialog theObject(
      ZoomInDialog::UNSPECIFIED_WIDTH,  640,
      ZoomInDialog::UNSPECIFIED_HEIGHT, 480,
      ZoomInDialog::SHOW_DIALOG
   );

   if(theObject.exec())
   {
      int width  = theObject.getUserSpecifiedWidth();
      int height = theObject.getUserSpecifiedHeight();

      const char *widthOption = ZoomInDialog::toString(
         theObject.getWidthOption()
      );

      const char *heightOption = ZoomInDialog::toString(
         theObject.getHeightOption()
      );

      cout << "width       : [" << width        << "]" << endl;
      cout << "height      : [" << height       << "]" << endl;
      cout << "widthOption : [" << widthOption  << "]" << endl;
      cout << "heightOption: [" << heightOption << "]" << endl;
   }
   else
   {
      cout << "Cancelled" << endl;
   }

   return(0);
}

#endif
