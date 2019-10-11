// Local Headers

#include "FalseBooleanNode.h"

FalseBooleanNode::FalseBooleanNode()
{
}

FalseBooleanNode::~FalseBooleanNode()
{
   // Nothing to do
}

int FalseBooleanNode::evaluate() const
{
   return(0);
}

ostream &FalseBooleanNode::print(ostream &out) const
{
   out << "true";
   return(out);
}
