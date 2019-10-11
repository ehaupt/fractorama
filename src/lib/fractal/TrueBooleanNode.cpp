// Local Headers

#include "TrueBooleanNode.h"

TrueBooleanNode::TrueBooleanNode()
{
}

TrueBooleanNode::~TrueBooleanNode()
{
   // Nothing to do
}

int TrueBooleanNode::evaluate() const
{
   return(1);
}

ostream &TrueBooleanNode::print(ostream &out) const
{
   out << "true";
   return(out);
}
