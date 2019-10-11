// Local Headers

#include "PolyRegionNode.h"
#include "ComplexNode.h"
#include "DoubleNode.h"
#include "tf.h"
#include "dmemory.h"

PolyRegionNode::PolyRegionNode(const ComplexNode **points, int count)
   :
   mPoints(points),
   mCount(count),
   mX(0),
   mY(0)
{
   DNEW(mX, double[mCount]);
   DNEW(mY, double[mCount]);
}

PolyRegionNode::~PolyRegionNode()
{
   for(int i = 0; i < mCount; i ++)
   {
      ComplexNode *node = (ComplexNode *)mPoints[i];
      DDELETE(node);
   }

   DADELETE(mPoints);
   DADELETE(mX);
   DADELETE(mY);
}

int PolyRegionNode::contains(const ComplexNode *point)  const
{
   // First, populate 'mX' and 'mY' with the values from our points -
   // we'll try to exclude the entire polygon first for speed ...

   double xMin = 0;
   double yMin = 0;
   double xMax = 0;
   double yMax = 0;

   int i = 0;

   for(i = 0; i < mCount; i ++)
   {
      dcomplex value = mPoints[i]->evaluate();
      mX[i]          = __REAL(value);
      mY[i]          = __IMAG(value);

      if(i == 0)
      {
         xMin = xMax = mX[i];
         yMin = yMax = mY[i];
      }
      else
      {
         if(mX[i] < xMin)      xMin = mX[i];
         else if(mX[i] > xMax) xMax = mX[i];

         if(mY[i] < yMin)      yMin = mY[i];
         else if(mY[i] > yMax) yMax = mY[i];
      }
   }

   dcomplex p = point->evaluate();
   double px  = __REAL(p);
   double py  = __IMAG(p);

   if(px < xMin || px > xMax || py < yMin || py > yMax)
      return(FALSE);

   // Alright, we've got to do the calculation to see if (px, py)
   // is inside the polygon or not - this densely packed (but accurate)
   // algorithm was lifted from the comp.graphics.algorithms faq

   int c = 0;
   int j = 0;

   for(i = 0, j = mCount - 1; i < mCount; j = i++)
   {
      if(
         ((mY[i] <= py && py < mY[j]) || (mY[j] <= py && py < mY[i])) &&
         px < (mX[j] - mX[i]) * (py - mY[i]) / (mY[j] - mY[i]) + mX[i]
      )
      {
         c = !c;
      }
   }

   return(c);
}

ostream &PolyRegionNode::print(ostream &out) const
{
   out << "r_poly(";

   for(int i = 0; i < mCount; i ++)
   {
      if(i > 0)
         out << ", ";

      mPoints[i]->print(out);
   }

   return(out << ")");
}
