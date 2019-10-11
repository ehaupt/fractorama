// Local Headers

#include "OrRegionNode.h"
#include "dmemory.h"

OrRegionNode::OrRegionNode(
   const RegionNode *first, const RegionNode *second
)  :
   mFirst(first),
   mSecond(second)
{
}

OrRegionNode::~OrRegionNode()
{
   DDELETE(mFirst);
   DDELETE(mSecond);
}

int OrRegionNode::contains(
   const ComplexNode *point
)  const
{
   return(
      mFirst->contains(point) || mSecond->contains(point)
   );
}

ostream &OrRegionNode::print(ostream &out) const
{
   out << "r_or(";
   mFirst->print(out);
   out << ", ";
   mSecond->print(out);
   return(out << ")");
}
