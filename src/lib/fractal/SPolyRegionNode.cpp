// Local Headers

#include "SPolyRegionNode.h"
#include "ComplexNode.h"
#include "AttributeDoubleNode.h"
#include "tf.h"
#include "dmemory.h"

SPolyRegionNode::SPolyRegionNode(
   const ComplexNode *center,
   const DoubleNode  *nSides,
   const DoubleNode  *radius,
   const DoubleNode  *angle
)
   :
   mCenter(center),
   mNSides(nSides),
   mRadius(radius),
   mAngle(angle)
{
}

SPolyRegionNode::~SPolyRegionNode()
{
   DDELETE(mCenter);
   DDELETE(mNSides);
   DDELETE(mRadius);
   DDELETE(mAngle);
}

int SPolyRegionNode::contains(const ComplexNode *point)  const
{
   int n = (int)(0.5 + mNSides->evaluate());

   if(n < 3)
      return(FALSE);

   dcomplex p = point->evaluate();
   dcomplex c = mCenter->evaluate();
   double   r = mRadius->evaluate();

   // Ok, first we translate 'p' relative to the polygon's center

   p -= c;

   // Now find the distance from p to the origin

   double dist = AttributeDoubleNode::magnitude(p);

   // if distance to the center of the polygon ('dist') is greater than
   // the polygon's radius we know the point is outside immediately

   if(dist > r)
      return(FALSE);

   // Ok, find out our polygon's offset angle and convert it to radians

   double a =
      mAngle->evaluate() / AttributeDoubleNode::DEGREES_PER_RADIAN;

   // Now get the angle that 'p' makes with our polygon's center

   double angle = AttributeDoubleNode::radians(p);

   // We want to do our calculations as if 'a' were zero so we adjust
   // 'angle' relative to 'a'

   angle -= a;

   // Ensure that 0 <= angle <= 2 * pi so that our 'modAngle'
   // calculation below will work properly

   while(angle < 0)
      angle += AttributeDoubleNode::TWO_PI;

   while(angle > AttributeDoubleNode::TWO_PI)
      angle -= AttributeDoubleNode::TWO_PI;

   double modAngle = AttributeDoubleNode::TWO_PI / n;

   angle = fmod(angle, modAngle);

   // Ok, now since this polygon is wholly regular we can consider 'angle'
   // as if it was within the first segment of the polygon.

   double farAngle = (AttributeDoubleNode::PI - modAngle) / 2;
   double other    = AttributeDoubleNode::PI - (angle + farAngle);

   // sin(other) / r == sin(farAngle) / dist
   //
   // dist * sin(other) == r * sin(farAngle)
   // dist = sin(farAngle) * r / sin(other)

   double d = r * sin(farAngle) / sin(other);

   return(dist <= d);
}

ostream &SPolyRegionNode::print(ostream &out) const
{
   out << "r_spoly(";
   mCenter->print(out);
   out << ", ";
   mNSides->print(out);
   out << ", ";
   mRadius->print(out);
   out << ", ";
   mAngle->print(out);
   out << ")";

   return(out);
}
