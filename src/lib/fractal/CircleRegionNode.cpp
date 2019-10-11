// Local Headers

#include "CircleRegionNode.h"
#include "ComplexNode.h"
#include "DoubleNode.h"
#include "dmemory.h"

CircleRegionNode::CircleRegionNode(
   const ComplexNode *center, const DoubleNode *radius
)  :
   mCenter(center),
   mRadius(radius)
{
}

CircleRegionNode::~CircleRegionNode()
{
   DDELETE(mCenter);
   DDELETE(mRadius);
}

int CircleRegionNode::contains(const ComplexNode *point)  const
{
   dcomplex p      = point->evaluate();
   double radius   = mRadius->evaluate();
   dcomplex center = mCenter->evaluate();

   double xDist = __REAL(p) - __REAL(center);
   double yDist = __IMAG(p) - __IMAG(center);

   return(xDist * xDist + yDist * yDist <= radius * radius);
}

ostream &CircleRegionNode::print(ostream &out) const
{
   out << "r_circle(";
   mCenter->print(out);
   out << ", ";
   mRadius->print(out);
   return(out << ")");
}
