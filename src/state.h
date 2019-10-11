#ifndef _STATE_H_
#   define _STATE_H_

#include "zoomoutdialog.h"
#include "zoomindialog.h"
#include "zoominsettings.h"

class Persist;

class State : public ZoomInSettings
{
   public:
      State(Persist *p);
      ~State();

      State *clone();

      char *getOpenDirectory();
      void setOpenDirectory(const char *value);

      char *getSaveDirectory();
      void setSaveDirectory(const char *value);

      void getDimensions(int *width, int *height);
      void setDimensions(int width, int height);

      void getZoomColor(int *red, int *green, int *blue);
      void setZoomColor(int red, int green, int blue);

      void getSplitSizes(int *top, int *bottom);
      void setSplitSizes(int top, int bottom);

      double getZoomOutFactor();
      void setZoomOutFactor(double value);

      // For our ZoomInSettings interface

      virtual ZoomInDialog::WidthOption getZoomInWidthOption();
      virtual ZoomInDialog::HeightOption getZoomInHeightOption();
      virtual int getZoomInWidth();
      virtual int getZoomInHeight();

      void setZoomInWidthOption(ZoomInDialog::WidthOption option);
      void setZoomInHeightOption(ZoomInDialog::HeightOption option);
      void setZoomInWidth(int width);
      void setZoomInHeight(int height);

      int getFontSize();
      void setFontSize(int size);

      int getAntiAlias();
      void setAntiAlias(int value);

   private:
      State(const State &);
      State &operator=(const State &);

      char *mOpenDirectory;
      char *mSaveDirectory;
      int mWidth, mHeight;
      int mRed, mGreen, mBlue;
      int mTop, mBottom;
      double mZoomOutFactor;
      ZoomInDialog::WidthOption  mZoomInWidthOption;
      ZoomInDialog::HeightOption mZoomInHeightOption;
      int mZoomInWidth;
      int mZoomInHeight;
      char *mFontName;
      int mFontSize;
      int mAntiAlias;
      Persist *mPersist;
};
#endif
