#ifndef _CIRCLE_REGION_NODE_H_
#   define _CIRCLE_REGION_NODE_H_

#include "RegionNode.h"

class DoubleNode;

class CircleRegionNode : public RegionNode
{
   public:
      CircleRegionNode(const ComplexNode *center, const DoubleNode *radius);

      virtual ~CircleRegionNode();

      virtual int contains(const ComplexNode *point) const;

      virtual ostream &print(ostream &out) const;

   private:
      CircleRegionNode(const CircleRegionNode &);
      CircleRegionNode& operator=(const CircleRegionNode &);

      const ComplexNode *mCenter;
      const DoubleNode  *mRadius;
};

#endif
