#ifndef _NOT_REGION_NODE_H_
#   define _NOT_REGION_NODE_H_

#include "RegionNode.h"

class NotRegionNode : public RegionNode
{
   public:
      NotRegionNode(const RegionNode *node);

      virtual ~NotRegionNode();

      virtual int contains(const ComplexNode *point) const;

      virtual ostream &print(ostream &out) const;

   private:
      NotRegionNode(const NotRegionNode &);
      NotRegionNode& operator=(const NotRegionNode &);

      const RegionNode *mNode;
};

#endif
