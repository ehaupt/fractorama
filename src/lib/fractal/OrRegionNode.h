#ifndef _OR_REGION_NODE_H_
#   define _OR_REGION_NODE_H_

#include "RegionNode.h"

class OrRegionNode : public RegionNode
{
   public:
      OrRegionNode(const RegionNode *first, const RegionNode *second);

      virtual ~OrRegionNode();

      virtual int contains(
         const ComplexNode *point
      ) const;

      virtual ostream &print(ostream &out) const;

   private:
      OrRegionNode(const OrRegionNode &);
      OrRegionNode& operator=(const OrRegionNode &);

      const RegionNode *mFirst;
      const RegionNode *mSecond;
};

#endif
