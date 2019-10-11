// Local Headers

#include "NotRegionNode.h"
#include "dmemory.h"

NotRegionNode::NotRegionNode(const RegionNode *node)
   :
   mNode(node)
{
}

NotRegionNode::~NotRegionNode()
{
   DDELETE(mNode);
}

int NotRegionNode::contains(const ComplexNode *point) const
{
   return(!mNode->contains(point));
}

ostream &NotRegionNode::print(ostream &out) const
{
   out << "r_not(";

   mNode->print(out);

   return(out << ")");
}
