#ifndef _ZOOMIN_OPTIONS_H_
#   define _ZOOMIN_OPTIONS_H_

#include "zoomindialog.h"

class ZoomInSettings
{
   public:
      virtual ~ZoomInSettings() {}
      virtual ZoomInDialog::WidthOption getZoomInWidthOption()   = 0;
      virtual ZoomInDialog::HeightOption getZoomInHeightOption() = 0;
      virtual int getZoomInWidth()                               = 0;
      virtual int getZoomInHeight()                              = 0;
};
#endif
