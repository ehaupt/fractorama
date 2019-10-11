// Local Headers

#include "XorRegionNode.h"
#include "dmemory.h"

XorRegionNode::XorRegionNode(
   const RegionNode *first, const RegionNode *second
)  :
   mFirst(first),
   mSecond(second)
{
}

XorRegionNode::~XorRegionNode()
{
   DDELETE(mFirst);
   DDELETE(mSecond);
}

int XorRegionNode::contains(const ComplexNode *point)  const
{
   int firstContains  = mFirst->contains(point);
   int secondContains = mSecond->contains(point);

   return(firstContains != secondContains);
}

ostream &XorRegionNode::print(ostream &out) const
{
   out << "r_xor(";
   mFirst->print(out);
   out << ", ";
   mSecond->print(out);
   return(out << ")");
}
