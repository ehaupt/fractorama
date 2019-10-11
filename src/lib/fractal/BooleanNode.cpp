#include "BooleanNode.h"

BooleanNode::BooleanNode()  {}
BooleanNode::~BooleanNode() {}

ostream &operator<<(ostream &out, const BooleanNode &n)
{
   return(n.print(out));
}
