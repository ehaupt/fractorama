#ifndef _AntiAliasDialog_H_
#   define _AntiAliasDialog_H_

#include <qdialog.h>

class QWidget;
class QCheckBox;

class AntiAliasDialog : public QDialog
{
   public:
      AntiAliasDialog(int antiAlias, QWidget *parent = 0);
      int getAntiAlias();

   private:
      QCheckBox *mBox;
};

#endif
