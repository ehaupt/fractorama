#include "DoubleNode.h"

DoubleNode::DoubleNode()
{
}

DoubleNode::~DoubleNode()
{
}

ostream &operator<<(ostream &out, const DoubleNode &n)
{
   return(n.print(out));
}
