#include "ConstantDoubleNode.h"

ConstantDoubleNode::ConstantDoubleNode(double value) : mValue(value) {}

double ConstantDoubleNode::evaluate() const
{
   return(mValue);
}

ostream &ConstantDoubleNode::print(ostream &out) const
{
   return(out << mValue);
}
