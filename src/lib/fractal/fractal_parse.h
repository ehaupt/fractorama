/*****************************************************************************
 * fractal_parse.h
 *****************************************************************************/

#ifndef _FRACTAL_PARSE_H_
#   define _FRACTAL_PARSE_H_

char *fractal_slurpFile(
   const char *fileName,
   char **errorMessagePointer
);

class Fractal;

Fractal *fractal_createFromText(
   const char *text,
   char **errorMessagePointer,
   int *errorLineNumberPointer
);

typedef struct
{
   double xStart;
   double yStart;
   double xEnd;
   double yEnd;
   double pixelWidth;
   double pixelHeight;

} FractalDefinition;

int fractal_createZoomBuffer(
   const char *buffer,
   char **zoomBufferPtr,
   double x0, double y0, double x1, double y1,
   char **errorMessagePointer,
   int *errorLineNumberPointer,
   void *clientData,
   void (*mapFunction)(
      FractalDefinition *parent,
      FractalDefinition *child,
      double x0, double y0, double x1, double y1,
      void *clientData
   )
);

#endif
