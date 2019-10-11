#ifndef _AND_REGION_NODE_H_
#   define _AND_REGION_NODE_H_

#include "RegionNode.h"

class AndRegionNode : public RegionNode
{
   public:
      AndRegionNode(const RegionNode *first, const RegionNode *second);

      virtual ~AndRegionNode();

      virtual int contains(const ComplexNode *point) const;

      virtual ostream &print(ostream &out) const;

   private:
      AndRegionNode(const AndRegionNode &);
      AndRegionNode& operator=(const AndRegionNode &);

      const RegionNode *mFirst;
      const RegionNode *mSecond;
};

#endif
