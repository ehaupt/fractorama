#ifndef _RECT_REGION_NODE_H_
#   define _RECT_REGION_NODE_H_

#include "RegionNode.h"

class DoubleNode;

class RectRegionNode : public RegionNode
{
   public:
      RectRegionNode(const ComplexNode *first, const ComplexNode *second);

      virtual ~RectRegionNode();

      virtual int contains(const ComplexNode *point) const;

      virtual ostream &print(ostream &out) const;

   private:
      RectRegionNode(const RectRegionNode &);
      RectRegionNode& operator=(const RectRegionNode &);

      const ComplexNode *mFirst;
      const ComplexNode *mSecond;
};

#endif
