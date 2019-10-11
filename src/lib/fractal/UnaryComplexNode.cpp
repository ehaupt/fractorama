// Local Headers

#include "UnaryComplexNode.h"
#include "dmemory.h"

UnaryComplexNode::UnaryComplexNode(const ComplexNode *nodePtr)
: mComplexNodePtr(nodePtr) {}

UnaryComplexNode::~UnaryComplexNode()
{
   DDELETE(mComplexNodePtr);
}

dcomplex UnaryComplexNode::evaluate() const
{
   return(-mComplexNodePtr->evaluate());
}

ostream &UnaryComplexNode::print(ostream &out) const
{
   out << "-";
   mComplexNodePtr->print(out);

   return(out);
}
