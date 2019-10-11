#include "ComplexNode.h"

ComplexNode::ComplexNode()
{
}

ComplexNode::~ComplexNode()
{
}

ostream &operator<<(ostream &out, const ComplexNode &n)
{
   return(n.print(out));
}
