// Local Headers

#include "EllipseRegionNode.h"
#include "ComplexNode.h"
#include "DoubleNode.h"
#include "tf.h"
#include "dmemory.h"

EllipseRegionNode::EllipseRegionNode(
   const ComplexNode *center,
   const DoubleNode  *xradius,
   const DoubleNode  *yradius
)  :
   mCenter(center),
   mXRadius(xradius),
   mYRadius(yradius)
{
}

EllipseRegionNode::~EllipseRegionNode()
{
   DDELETE(mCenter);
   DDELETE(mXRadius);
   DDELETE(mYRadius);
}

int EllipseRegionNode::contains(const ComplexNode *point)  const
{
   double width  = mXRadius->evaluate();
   double height = mYRadius->evaluate();

   if(width <= 0 || height <= 0)
      return(FALSE);

   dcomplex center = mCenter->evaluate();
   double   cx     = __REAL(center);
   double   cy     = __IMAG(center);

   dcomplex p  = point->evaluate();
   double   px = __REAL(p);
   double   py = __IMAG(p);

   // Normalize the coordinates (px, py) compared to the ellipse
   // having a center of (0, 0) and a radius of 0.5

   double normx = (px - cx) / width;
   double normy = (py - cy) / height;

   return(normx * normx + normy * normy <= 1);
}

ostream &EllipseRegionNode::print(ostream &out) const
{
   out << "r_ellipse(";
   mCenter->print(out);
   out << ", ";
   mXRadius->print(out);
   out << ", ";
   mYRadius->print(out);
   return(out << ")");
}
