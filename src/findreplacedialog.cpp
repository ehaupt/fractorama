// Qt Headers

#include <qlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include <qmessagebox.h>
#include <qclipboard.h>
#include <qapplication.h>
#include <qmultilineedit.h>

// Local Headers

#include "findreplacedialog.h"

FindReplaceDialog::FindReplaceDialog(QWidget *parent, QMultiLineEdit *edit)
   :
   QDialog(parent, "FindReplaceDialog"),
   mEdit(edit),
   mFindButton(0),
   mReplaceButton(0),
   mReplaceAllButton(0),
   mFind(0),
   mReplace(0),
   mCaseSensitive(0),
   mLineNumber(0),
   mColumnNumber(0)
{
   QBoxLayout *topLayout = new QVBoxLayout(this, QBoxLayout::Down);

   topLayout->addSpacing(10);

   // Add fields ...

   QGridLayout *fields = new QGridLayout(topLayout, 2, 4, 10);

   fields->addColSpacing(0, 10);
   fields->addColSpacing(3, 10);

   fields->addWidget(new QLabel("Find:", this), 0, 1);

   mFind = new QLineEdit(this);

   fields->addWidget(mFind, 0, 2);

   fields->addWidget(new QLabel("Replace With:", this), 1, 1);

   mReplace = new QLineEdit(this);

   fields->addWidget(mReplace, 1, 2);

   QBoxLayout *middle = new QVBoxLayout(topLayout, QVBoxLayout::Down);

   middle->addSpacing(10);

   QBoxLayout *middleHorizontal = new QHBoxLayout(middle);

   QCheckBox *honorCase = new QCheckBox("Case Sensitive", this);

   QObject::connect(
      honorCase,
      SIGNAL(clicked()),
      this,
      SLOT(toggleCaseSensitive())
   );

   middleHorizontal->addSpacing(10);
   middleHorizontal->addWidget(honorCase);

   middle->addSpacing(10);

   // Add buttons ...

   QBoxLayout *buttons = new QHBoxLayout(topLayout);

   mFindButton              = new QPushButton("&Find",        this);
   mReplaceButton           = new QPushButton("&Replace",     this);
   mReplaceAllButton        = new QPushButton("Replace &All", this);
   QPushButton *closeButton = new QPushButton("&Close",       this);

   QObject::connect(
      closeButton,
      SIGNAL(clicked()),
      this,
      SLOT(hide())
   );

   QObject::connect(
      mFind,
      SIGNAL(textChanged(const QString &)),
      this,
      SLOT(handleTextChanged())
   );

   QObject::connect(
      mReplace,
      SIGNAL(textChanged(const QString &)),
      this,
      SLOT(handleTextChanged())
   );

   QObject::connect(
      mFindButton,
      SIGNAL(clicked()),
      this,
      SLOT(doFind())
   );

   QObject::connect(
      mReplaceButton,
      SIGNAL(clicked()),
      this,
      SLOT(doReplace())
   );

   QObject::connect(
      mReplaceAllButton,
      SIGNAL(clicked()),
      this,
      SLOT(doReplaceAll())
   );

   mFindButton->setEnabled(FALSE);
   mReplaceButton->setEnabled(FALSE);
   mReplaceAllButton->setEnabled(FALSE);

   buttons->addSpacing(10);
   buttons->addWidget(mFindButton);
   buttons->addSpacing(10);
   buttons->addWidget(mReplaceButton);
   buttons->addSpacing(10);
   buttons->addWidget(mReplaceAllButton);
   buttons->addSpacing(10);
   buttons->addWidget(closeButton);
   buttons->addSpacing(10);

   topLayout->addSpacing(10);
}

FindReplaceDialog::~FindReplaceDialog()
{
   // Nothing to do
}

void FindReplaceDialog::show()
{
   QDialog::show();
   mFind->setFocus();
}

void FindReplaceDialog::handleTextChanged()
{
   QString findStripped = mFind->text().stripWhiteSpace();

   if(findStripped.isEmpty())
   {
      mFindButton->setEnabled(FALSE);
      mReplaceButton->setEnabled(FALSE);
      mReplaceAllButton->setEnabled(FALSE);
   }
   else
   {
      mFindButton->setEnabled(TRUE);

      QString replaceStripped = mReplace->text().stripWhiteSpace();

      if(replaceStripped.isEmpty())
      {
         mReplaceButton->setEnabled(FALSE);
         mReplaceAllButton->setEnabled(FALSE);
      }
      else
      {
         mReplaceButton->setEnabled(TRUE);
         mReplaceAllButton->setEnabled(TRUE);
      }
   }
}

void FindReplaceDialog::toggleCaseSensitive()
{
   mCaseSensitive = !mCaseSensitive;
}

void FindReplaceDialog::doFind()
{
   // JFD: This function has problems when the found string occurs at
   //      the end of the line (or very near the end of the line).
   //      It becomes confused and keeps searching the same line
   //      over and over, I suspect the problem is with [*] below

   // There will always be at least one line in 'mEdit' (though it might
   // be empty).  Further, lines are accessed individually by calling
   // mEdit->textLine(i) where i >= 0 && i < nLines

   int nLines = mEdit->numLines();

   // Acquire the text we're to search for

   QString text = mFind->text();

   // Pick up where we left off unless those values are now invalid

   if(mLineNumber >= nLines)
   {
      mLineNumber   = 0;
      mColumnNumber = 0;
   }

   // We use 'i <= nLines' so that if we've got just one occurrence of the
   // search string we'll end up back on it

   for(int i = 0; i <= nLines; i ++)
   {
      QString theLine = mEdit->textLine(mLineNumber);

      if(i == 0)
      {
         if(mColumnNumber >= (int)theLine.length())
            mColumnNumber = 0;
      }

      int offset = theLine.find(text, mColumnNumber, mCaseSensitive);

      if(offset != -1)
      {
         doHighlight(mLineNumber, offset, text);

         if(offset + text.length() + 1 >= theLine.length())
         {
            mColumnNumber = 0;

            if(++mLineNumber == nLines)
               mLineNumber = 0;
         }
         else
            mColumnNumber = offset + text.length() + 1;

         return;
      }

      if(i == 0)
         mColumnNumber = 0;

      if(++mLineNumber == nLines)
         mLineNumber = 0;
   }

   QString theMessage("Search string: [");
   theMessage.append(text);
   theMessage.append("] not found");

   QMessageBox::information(this, "Not Found", theMessage);
}

void FindReplaceDialog::doReplace()
{
   // Ok, what *should* be the case here is that the search
   // string is currently highlighted ... if this true then we'll
   // do nothing

   QString marked = mEdit->selectedText();
   QString text   = mFind->text();

   if(marked.find(text, 0, mCaseSensitive) != 0)
      return;

   // Replace the text ...

   QClipboard *cb      = QApplication::clipboard();
   QString replaceText = mReplace->text();

   cb->setText(replaceText);

   mEdit->paste();

   // Now adjust 'mColumnNumber' if we need to ... if the text
   // was found at the end of the line we will have moved
   // mColumnNumber and mLineNumber to 0 and the next line respectively
   // and in that case we'll not be updating mColumnNumber

   if(mColumnNumber > 0)
      mColumnNumber += (replaceText.length() - text.length());
}

void FindReplaceDialog::doReplaceAll()
{
   // Here we'll do our clipboard trick again but apply it to every
   // occurrence of the search text

   int nLines          = mEdit->numLines();
   QClipboard *cb      = QApplication::clipboard();
   QString text        = mFind->text();
   QString replaceText = mReplace->text();
   int replaceLength   = replaceText.length();

   cb->setText(replaceText);

   for(int i = 0; i < nLines; i ++)
   {
      int offset = 0;

      while(TRUE)
      {
         QString theLine = mEdit->textLine(i);

         if((offset = theLine.find(text, offset, mCaseSensitive)) == -1)
            break;

         // Ok, highlight the text and replace it ...

         doHighlight(i, offset, text);
         mEdit->paste();

         // Adjust 'offset' to be on character beyond the replacement
         // string

         offset += replaceLength + 1;
      }
   }
}

void FindReplaceDialog::doHighlight(int line, int column, const QString &text)
{
   // Put the cursor on the correct line ...

   mEdit->setCursorPosition(line, 0);

   // Now highlight the text

   mEdit->insertAt("", line, column, TRUE);

   int length = text.length();

   for(int i = 0; i <= length; i ++)
      mEdit->setCursorPosition(line, column + i, TRUE);
}
