#ifndef _XOR_REGION_NODE_H_
#   define _XOR_REGION_NODE_H_

#include "RegionNode.h"

class XorRegionNode : public RegionNode
{
   public:
      XorRegionNode(const RegionNode *first, const RegionNode *second);

      virtual ~XorRegionNode();

      virtual int contains(const ComplexNode *point) const;

      virtual ostream &print(ostream &out) const;

   private:
      XorRegionNode(const XorRegionNode &);
      XorRegionNode& operator=(const XorRegionNode &);

      const RegionNode *mFirst;
      const RegionNode *mSecond;
};

#endif
