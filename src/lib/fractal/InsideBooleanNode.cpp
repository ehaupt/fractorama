// Local Headers

#include "InsideBooleanNode.h"
#include "ComplexNode.h"
#include "RegionNode.h"
#include "dmemory.h"

InsideBooleanNode::InsideBooleanNode(
   const ComplexNode *point, const RegionNode *region
)  :
   mPoint(point),
   mRegion(region)
{
}

InsideBooleanNode::~InsideBooleanNode()
{
   DDELETE(mPoint);
   DDELETE(mRegion);
}

int InsideBooleanNode::evaluate() const
{
   return(mRegion->contains(mPoint));
}

ostream &InsideBooleanNode::print(ostream &out) const
{
   out << "inside(";
   mPoint->print(out);
   out << ", ";
   mRegion->print(out);

   return(out << ")");
}
