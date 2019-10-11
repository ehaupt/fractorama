// Local Headers

#include "CrossRegionNode.h"
#include "ComplexNode.h"
#include "DoubleNode.h"
#include "tf.h"
#include "dmemory.h"

CrossRegionNode::CrossRegionNode(
   const ComplexNode *p1,
   const ComplexNode *p2,
   const DoubleNode  *barWidth,
   const DoubleNode  *barHeight     
)  :
   mP1(p1),
   mP2(p2),
   mBarWidth(barWidth),
   mBarHeight(barHeight)
{
}

CrossRegionNode::~CrossRegionNode()
{
   DDELETE(mP1);
   DDELETE(mP2);
   DDELETE(mBarWidth);
   DDELETE(mBarHeight);
}

int CrossRegionNode::contains(
   const ComplexNode *point
) const
{
   dcomplex p1 = mP1->evaluate();
   dcomplex p2 = mP2->evaluate();
   dcomplex p  = point->evaluate();

   double p1x = __REAL(p1);
   double p1y = __IMAG(p1);

   double p2x = __REAL(p2);
   double p2y = __IMAG(p2);

   double px  = __REAL(p);
   double py  = __IMAG(p);

   // See if 'p' is outside our area completely first ...

   if(p1x < p2x)
   {
      if(px < p1x || px > p2x)
         return(FALSE);
   }
   else
   {
      if(px < p2x || px > p1x)
         return(FALSE);
   }

   if(p1y < p2y)
   {
      if(py < p1y || py > p2y)
         return(FALSE);
   }
   else
   {
      if(py < p2y || py > p1y)
         return(FALSE);
   }

   double xCrossCenter = (p1x + p2x) / 2.0;
   double yCrossCenter = (p1y + p2y) / 2.0;

   double barWidth2  = mBarWidth->evaluate()  / 2.0;
   double barHeight2 = mBarHeight->evaluate() / 2.0;

   if(px >= xCrossCenter - barWidth2 && px <= xCrossCenter + barWidth2)
      return(TRUE);

   if(py >= yCrossCenter - barHeight2 && py <= yCrossCenter + barHeight2)
      return(TRUE);

   return(FALSE);
}

ostream &CrossRegionNode::print(ostream &out) const
{
   out << "r_cross(";
   mP1->print(out); out << ", ";
   mP2->print(out); out << ", ";
   mBarWidth->print(out); out << ", ";
   mBarHeight->print(out);

   return(out << ")");
}
