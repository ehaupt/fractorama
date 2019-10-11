#include "map.h"
#include "zoominsettings.h"

void Map::mapFunction(
   FractalDefinition *parent,
   FractalDefinition *child,
   double x0, double y0, double x1, double y1,
   void *clientData
)
{
   double srcX0 = 0.0;
   double srcY0 = parent->pixelHeight;

   double srcX1 = parent->pixelWidth;
   double srcY1 = 0.0;

   double xRatio = (parent->xEnd - parent->xStart) / (srcX1 - srcX0);
   double yRatio = (parent->yEnd - parent->yStart) / (srcY1 - srcY0);

   double xZoom0 = 0.0;
   double yZoom0 = 0.0;
   double xZoom1 = 0.0;
   double yZoom1 = 0.0;

   if(x0 < x1)
   {
      xZoom0 = x0;
      xZoom1 = x1;
   }
   else
   {
      xZoom0 = x1;
      xZoom1 = x0;
   }

   if(y0 < y1)
   {
      yZoom0 = y1;
      yZoom1 = y0;
   }
   else
   {
      yZoom0 = y0;
      yZoom1 = y1;
   }

   child->xStart = (xZoom0 - srcX0) * xRatio + parent->xStart;
   child->yStart = (yZoom0 - srcY0) * yRatio + parent->yStart;

   child->xEnd = (xZoom1 - srcX0) * xRatio + parent->xStart;
   child->yEnd = (yZoom1 - srcY0) * yRatio + parent->yStart;

   ZoomInSettings *settings = (ZoomInSettings *)clientData;

   double height = 0.0;
   double width  = 0.0;

   switch(settings->getZoomInHeightOption())
   {
      case ZoomInDialog::UNSPECIFIED_HEIGHT:
      {
         height = 0.0;
      }
      break;

      case ZoomInDialog::USE_PARENT_HEIGHT:
      {
         height = parent->pixelHeight; 
      }
      break;

      case ZoomInDialog::USER_SPECIFIED_HEIGHT:
      {
         height = (double)settings->getZoomInHeight();
      }
      break;
   }

   switch(settings->getZoomInWidthOption())
   {
      case ZoomInDialog::UNSPECIFIED_WIDTH:
      {
         width = 0.0;
      }
      break;

      case ZoomInDialog::USE_PARENT_WIDTH:
      {
         width = parent->pixelWidth; 
      }
      break;

      case ZoomInDialog::USER_SPECIFIED_WIDTH:
      {
         width = (double)settings->getZoomInWidth();
      }
      break;
   }

   if(height == 0.0 && width == 0.0)
   {
      double ratio = parent->pixelWidth / (xZoom1 - xZoom0);

      if(ratio * (yZoom0 - yZoom1) > parent->pixelHeight)
         ratio = parent->pixelHeight / (yZoom0 - yZoom1);

      child->pixelWidth  = (xZoom1 - xZoom0) * ratio;
      child->pixelHeight = (yZoom0 - yZoom1) * ratio;
   }
   else if(height == 0.0)
   {
      child->pixelWidth  = width;
      child->pixelHeight = width / (xZoom1 - xZoom0) * (yZoom0 - yZoom1);
   }
   else if(width == 0.0)
   {
      child->pixelHeight = height;
      child->pixelWidth  = height / (yZoom0 - yZoom1) * (xZoom1 - xZoom0);
   }
   else
   {
      child->pixelWidth  = width;
      child->pixelHeight = height;
   }
}
