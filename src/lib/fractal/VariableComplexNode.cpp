// C/C++ Headers

#include <string.h>

// Local Headers

#include "VariableComplexNode.h"
#include "dmemory.h"

VariableComplexNode::VariableComplexNode(
   char *variableName, dcomplex *ptr
)  : mPtr(ptr)
{
   DNEW(mName, char[strlen(variableName) + 1]);
   strcpy(mName, variableName);
}

VariableComplexNode::~VariableComplexNode()
{
   DADELETE(mName);
}

ostream &VariableComplexNode::print(ostream &out) const
{
   return(out << mName);
}
