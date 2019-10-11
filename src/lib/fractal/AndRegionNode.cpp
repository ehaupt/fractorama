// Local Headers

#include "AndRegionNode.h"
#include "dmemory.h"

AndRegionNode::AndRegionNode(
   const RegionNode *first, const RegionNode *second
)  :
   mFirst(first),
   mSecond(second)
{
}

AndRegionNode::~AndRegionNode()
{
   DDELETE(mFirst);
   DDELETE(mSecond);
}

int AndRegionNode::contains(const ComplexNode *point)  const
{
   return(
      mFirst->contains(point) && mSecond->contains(point)
   );
}

ostream &AndRegionNode::print(ostream &out) const
{
   out << "r_and(";
   mFirst->print(out);
   out << ", ";
   mSecond->print(out);
   return(out << ")");
}
