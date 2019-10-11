// Local Headers

#include "UnaryDoubleNode.h"
#include "dmemory.h"

UnaryDoubleNode::UnaryDoubleNode(const DoubleNode *nodePtr)
   : mNodePtr(nodePtr) {}

UnaryDoubleNode::~UnaryDoubleNode()
{
   DDELETE(mNodePtr);
}

double UnaryDoubleNode::evaluate() const
{
   return(-mNodePtr->evaluate());
}

ostream &UnaryDoubleNode::print(ostream &out) const
{
   out << "-";
   mNodePtr->print(out);

   return(out);
}
