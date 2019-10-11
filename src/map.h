#ifndef _MAP_H_
#   define _MAP_H_

#include "fractal_parse.h"

class Map
{
   public:
      static void mapFunction(
         FractalDefinition *parent,
         FractalDefinition *child,
         double x0, double y0, double x1, double y1,
         void *clientData
      );
};

#endif
