#include <stdlib.h>
#include <sstream>

using std::ostringstream;

#include "GradientColorNode.h"
#include "ColorTable.h"
#include "dmemory.h"

GradientColorNode *GradientColorNode::create(
   int size, ColorStack &theStack, int count, string &errMsg
)
{
   if(count < 2 || size < count)
   {
      ostringstream o;

      o << "Illegal gradient requested\n"
         << "size of the gradient: [" << size << "]\n"
         << "colors in the gradient: [" << count << "]";

      errMsg = o.str();

      return(0);
   }

   GradientColorNode *ptr = 0;
   DNEW(ptr, GradientColorNode(size, theStack, count)); 
   return(ptr);
}

GradientColorNode::GradientColorNode(
   int size, ColorStack &theStack, int count
) : mSize(size), mTable(0)
{
   // Acquire the colors to be used in our gradient

   int **colors = 0;
   int i        = count - 1;

   DNEW(colors, int *[count]);

   while(i >= 0)
   {
      const int *iPtr = theStack.pop();
      colors[i--] = (int *)iPtr;
   }

   double factor = (size - 1.0) / (count - 1.0);
   double delta[3] = { 0.0, 0.0, 0.0 };

   double low      = -factor;
   double high     = 0.0;
   int index       = -1;
   int j           = 0;

   DNEW(mTable, int *[size]);

   for(i = 0; i < size; i ++)
   {
      if(i == 0 || i > high)
      {
         low  += factor;
         high += factor;
         index++;

         for(j = 0; j < 3; j ++)
            delta[j] = (colors[index + 1][j] - colors[index][j]);
      }

      DNEW(mTable[i], int[3]);

      double value = (i - low) / factor;

      for(j = 0; j < 3; j ++)
         mTable[i][j] = (int)(colors[index][j] + delta[j] * value + 0.5);
   }

   for(i = 0; i < count; i ++)
      DADELETE(colors[i]);

   DADELETE(colors);
}

GradientColorNode::~GradientColorNode()
{
   for(int i = 0; i < mSize; i ++)
      DADELETE(mTable[i]);

   DADELETE(mTable);
}

ostream &GradientColorNode::print(ostream &out) const
{
   for(int i = 0; i < mSize; i ++)
   {
      if(i > 0) out << "\n";

      out << "entry[" << i << "] (" <<
         mTable[i][0] << ", " <<
         mTable[i][1] << ", " <<
         mTable[i][2] << ")";
   }

   return(out);
}

void GradientColorNode::process(ColorTable &theTable) const
{ 
   for(int i = 0; i < mSize; i ++)
      theTable.addEntry(mTable[i][0], mTable[i][1], mTable[i][2]);
}
