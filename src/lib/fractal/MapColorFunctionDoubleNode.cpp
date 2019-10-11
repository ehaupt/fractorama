// C/C++ Headers

#include <string.h>
#include <math.h>

// Local Headers

#include "MapColorFunctionDoubleNode.h"
#include "TwoArgFunctionDoubleNode.h"
#include "dmemory.h"

MapColorFunctionDoubleNode::MapColorFunctionDoubleNode()
   :
   mArgs(0),
   mArgCount(0)
{
}

MapColorFunctionDoubleNode::~MapColorFunctionDoubleNode()
{
   for(int i = 0; i < mArgCount; i ++)
      DDELETE(mArgs[i]);

   DADELETE(mArgs);
}

#define MIN(x, y) TwoArgFunctionDoubleNode::min(x, y)
#define MAX(x, y) TwoArgFunctionDoubleNode::max(x, y)

double MapColorFunctionDoubleNode::evaluate() const
{
   double value = MIN(1.0, MAX(0.0, mArgs[0]->evaluate()));

   // Ok, we've got mArgCount - 1 additional arguments to process
   // the first (mArgCount - 1) / 2 + 1 arguments are color values
   // the last (mArgCount - 1) / 2 arguments are our percentages.
   // We now go through the percentages until we find the span
   // containing 'value'

   double total = 0.0;
   int start    = (mArgCount / 2) + 1;

   for(int i = start; i < mArgCount; i ++)
   {
      // If this is the last percentage value we actually ignore the
      // supplied value and instead and calculate it based upon:
      //    1.0 - (the total we've encountered thusfar)

      double percentage = (i + 1 == mArgCount ?
         1.0 - total :
         mArgs[i]->evaluate() / 100.0
      );

      // Ok, are we where we need to be?

      if(value <= total + percentage)
      {
         // Yep, so grab the two associated color values

         int index1 = 1 + (i - start);
         int index2 = index1 + 1;

         double color1 = mArgs[index1]->evaluate();
         double color2 = mArgs[index2]->evaluate();
         double ratio  = (value - total) / percentage;

         value = color1 + (color2 - color1) * ratio;
         break;
      }

      total += percentage;
   }

   return(value);
}

ostream &MapColorFunctionDoubleNode::print(ostream &out) const
{
   out << "map_color" << "(";

   for(int i = 0; i < mArgCount; i ++)
   {
      if(i > 0)
         out << ", ";

      mArgs[i]->print(out);
   }

   return(out << ")");
}

int MapColorFunctionDoubleNode::size() const
{
   return(mArgCount);
}

void MapColorFunctionDoubleNode::addArgument(const DoubleNode *arg)
{
   const DoubleNode **newArgs = 0;
   DNEW(newArgs, const DoubleNode *[mArgCount + 1]);

   for(int i = 0; i < mArgCount; i ++)
      newArgs[i] = mArgs[i];

   newArgs[mArgCount] = arg;

   DADELETE(mArgs);
   mArgCount++;

   mArgs = newArgs;
}
