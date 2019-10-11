// Local Headers

#include "RectRegionNode.h"
#include "ComplexNode.h"
#include "DoubleNode.h"
#include "tf.h"
#include "dmemory.h"

RectRegionNode::RectRegionNode(
   const ComplexNode *first, const ComplexNode *second
)  :
   mFirst(first),
   mSecond(second)
{
}

RectRegionNode::~RectRegionNode()
{
   DDELETE(mFirst);
   DDELETE(mSecond);
}

int RectRegionNode::contains(
   const ComplexNode *point
)  const
{
   dcomplex first  = mFirst->evaluate();
   dcomplex second = mSecond->evaluate();

   double xFirst  = __REAL(first);
   double yFirst  = __IMAG(first);
   double xSecond = __REAL(second);
   double ySecond = __IMAG(second);

   dcomplex p = point->evaluate();
   double px  = __REAL(p);
   double py  = __IMAG(p);

   double xMin = (xFirst < xSecond ? xFirst : xSecond);
   double yMin = (yFirst < ySecond ? yFirst : ySecond);
   double xMax = (xFirst > xSecond ? xFirst : xSecond);
   double yMax = (yFirst > ySecond ? yFirst : ySecond);

   if(px < xMin || px > xMax || py < yMin || py > yMax)
      return(FALSE);

   return(TRUE);
}

ostream &RectRegionNode::print(ostream &out) const
{
   out << "r_rect(";
   mFirst->print(out);
   out << ", ";
   mSecond->print(out);
   return(out << ")");
}
