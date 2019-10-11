#include <string.h>
#include <math.h>

// Local Headers

#include "ThreeArgFunctionDoubleNode.h"
#include "AttributeDoubleNode.h"
#include "HSVSetColorStatement.h"
#include "dmemory.h"

ThreeArgFunctionDoubleNode::ThreeArgFunctionDoubleNode(
   char *name,
   ThreeArgFunctionDoublePointer ptr,
   const DoubleNode *firstPtr,
   const DoubleNode *secondPtr,
   const DoubleNode *thirdPtr
)  :
   mPtr(ptr),
   mFirstPtr(firstPtr),
   mSecondPtr(secondPtr),
   mThirdPtr(thirdPtr)
{
   DNEW(mName, char[strlen(name) + 1]);
   strcpy(mName, name);
}

ThreeArgFunctionDoubleNode::~ThreeArgFunctionDoubleNode()
{
   DADELETE(mName);

   DDELETE(mFirstPtr);
   DDELETE(mSecondPtr);
   DDELETE(mThirdPtr);
}

double ThreeArgFunctionDoubleNode::evaluate() const
{
   return(
      mPtr(
         mFirstPtr->evaluate(),
         mSecondPtr->evaluate(),
         mThirdPtr->evaluate()
      )
   );
}

ostream &ThreeArgFunctionDoubleNode::print(ostream &out) const
{
   out << mName << "(";
   mFirstPtr->print(out);
   out << ", ";
   mSecondPtr->print(out);
   out << ", ";
   mThirdPtr->print(out);
   out << ")";

   return(out);
}

/*****************************************************************************
 * Our current set of 3 arg functions
 *****************************************************************************/

static double get_sin_color(
   double value, double start, double step
)
{
   value = -cos(AttributeDoubleNode::TWO_PI * value);

   value = value * 127 + 127;

   value = value * step + start;

   value /= 360;

   value = sin(AttributeDoubleNode::PI * value);

   value = value * 128 + 127;

   return(value < 0 ? 0 : value > 255 ? 255 : value);
}

static double get_hsv_red(
   double h, double s, double v
)
{
   double r, g, b;
   HSVSetColorStatement::hsv2rgb(h, s, v, &r, &g, &b);
   return(r);
}

static double get_hsv_green(
   double h, double s, double v
)
{
   double r, g, b;
   HSVSetColorStatement::hsv2rgb(h, s, v, &r, &g, &b);
   return(g);
}

static double get_hsv_blue(
   double h, double s, double v
)
{
   double r, g, b;
   HSVSetColorStatement::hsv2rgb(h, s, v, &r, &g, &b);
   return(b);
}

static double get_cos_color(
   double value, double offset, double scale
)
{
   double theOffset = AttributeDoubleNode::PI * (offset / 255.0);

   double result = cos(
      theOffset + AttributeDoubleNode::PI +
      scale * value * 2.0 * AttributeDoubleNode::PI
   );

   return(127.5 * (1.0 + result));
}

ThreeArgFunctionDoublePointer ThreeArgFunctionDoubleNode::lookup(char *name)
{
   struct Table
   {
      ThreeArgFunctionDoublePointer ptr;
      char *name;
   };

   static Table t[] =
   {
      { get_sin_color, "get_sin_color" },
      { get_hsv_red,   "get_hsv_red"   },
      { get_hsv_green, "get_hsv_green" },
      { get_hsv_blue,  "get_hsv_blue"  },
      { get_cos_color, "get_cos_color" },
   };

   int size = sizeof(t) / sizeof(t[0]);

   for(int i = 0; i < size; i ++)
      if(strcmp(t[i].name, name) == 0)
         return(t[i].ptr);

   return(0);
}
