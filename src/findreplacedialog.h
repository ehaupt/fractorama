#ifndef _FIND_REPLACE_DIALOG_H_
#   define _FIND_REPLACE_DIALOG_H_

#include <qdialog.h>

class QPushButton;
class QLineEdit;
class QMultiLineEdit;

class FindReplaceDialog : public QDialog
{
   Q_OBJECT

   public:
      FindReplaceDialog(QWidget *parent, QMultiLineEdit *edit);
      ~FindReplaceDialog();
      void show();

   private slots:
      void handleTextChanged();
      void toggleCaseSensitive();
      void doFind();
      void doReplace();
      void doReplaceAll();

   private:
      void doHighlight(int line, int column, const QString &text);

      QMultiLineEdit *mEdit;
      QPushButton   *mFindButton;
      QPushButton   *mReplaceButton;
      QPushButton   *mReplaceAllButton;
      QLineEdit     *mFind;
      QLineEdit     *mReplace;
      int           mCaseSensitive;
      int           mLineNumber;
      int           mColumnNumber;
};

#endif
