#ifndef _SPOLY_REGION_NODE_H_
#   define _SPOLY_REGION_NODE_H_

#include "RegionNode.h"

class DoubleNode;

class SPolyRegionNode : public RegionNode
{
   public:
      SPolyRegionNode(
         const ComplexNode *center,
         const DoubleNode  *nSides,
         const DoubleNode  *radius,
         const DoubleNode  *angle
      );

      virtual ~SPolyRegionNode();

      virtual int contains(
         const ComplexNode *point
      ) const;

      virtual ostream &print(ostream &out) const;

   private:
      SPolyRegionNode(const SPolyRegionNode &);
      SPolyRegionNode& operator=(const SPolyRegionNode &);

      const ComplexNode *mCenter;
      const DoubleNode  *mNSides;
      const DoubleNode  *mRadius;
      const DoubleNode  *mAngle;
};

#endif
