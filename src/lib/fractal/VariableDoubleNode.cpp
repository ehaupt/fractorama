// C/C++ Headers

#include <string.h>

// Local Headers

#include "VariableDoubleNode.h"
#include "dmemory.h"

VariableDoubleNode::VariableDoubleNode(char *variableName, const double *ptr)
   : mPtr(ptr)
{
   DNEW(mName, char[strlen(variableName) + 1]);
   strcpy(mName, variableName);
}

VariableDoubleNode::~VariableDoubleNode()
{
   DADELETE(mName);
}

ostream &VariableDoubleNode::print(ostream &out) const
{
   return(out << "$" << mName);
}
