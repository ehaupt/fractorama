#ifndef _ZoomInDialog_H_
#   define _ZoomInDialog_H_

#include <qdialog.h>

class QWidget;
class QLineEdit;

class ZoomInDialog : public QDialog
{
   Q_OBJECT

   public:
      typedef enum
      {
         UNSPECIFIED_WIDTH,
         USE_PARENT_WIDTH,
         USER_SPECIFIED_WIDTH

      }  WidthOption;

      typedef enum
      {
         UNSPECIFIED_HEIGHT,
         USE_PARENT_HEIGHT,
         USER_SPECIFIED_HEIGHT

      }  HeightOption;

      ZoomInDialog(
         WidthOption widthOption,
         int userWidth,
         HeightOption heightOption,
         int userHeight,
         QWidget *parent = 0
      );

      int getUserSpecifiedWidth();
      int getUserSpecifiedHeight();
      WidthOption getWidthOption();
      HeightOption getHeightOption();

      static const char *toString(WidthOption option);
      static const char *toString(HeightOption option);
      static WidthOption widthOptionFromString(const char *s);
      static HeightOption heightOptionFromString(const char *s);

   private:
      ZoomInDialog(const ZoomInDialog &);
      ZoomInDialog &operator=(const ZoomInDialog &);

      void setField(int value, QLineEdit *field);

      QLineEdit *mWidthEdit;
      QLineEdit *mHeightEdit;
      WidthOption mWidthOption;
      HeightOption mHeightOption;

   private slots:
      void slotWidthOptionChanged(int which);
      void slotHeightOptionChanged(int which);

   protected slots:
      void done(int value);
};

#endif
