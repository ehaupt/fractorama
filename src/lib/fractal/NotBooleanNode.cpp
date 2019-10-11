// Local Headers

#include "NotBooleanNode.h"
#include "dmemory.h"

NotBooleanNode::NotBooleanNode(const BooleanNode *node)
   :
   mNode(node)
{
}

NotBooleanNode::~NotBooleanNode()
{
   DDELETE(mNode);
}

int NotBooleanNode::evaluate() const
{
   return(!mNode->evaluate());
}

ostream &NotBooleanNode::print(ostream &out) const
{
   out << "!";
   mNode->print(out);
   return(out);
}
