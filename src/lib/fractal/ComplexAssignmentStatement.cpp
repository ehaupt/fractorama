// C/C++ Headers

#include <string.h>

// Local Headers

#include "ComplexAssignmentStatement.h"
#include "ComplexNode.h"
#include "dmemory.h"

ComplexAssignmentStatement::ComplexAssignmentStatement(
   dcomplex *vptr,
   char *name,
   const ComplexNode *ptr,
   int isPostAssignment
) :
   mVPtr(vptr),
   mPtr(ptr),
   mIsPostAssignment(isPostAssignment)
{
   DNEW(mName, char[strlen(name) + 1]);
   strcpy(mName, name);
}

ComplexAssignmentStatement::~ComplexAssignmentStatement()
{
   DADELETE(mName);
   DDELETE(mPtr);
}

int ComplexAssignmentStatement::execute(
   InfiniteLoopCallback *, LoopControl *
) const
{
   *mVPtr = mPtr->evaluate();
   return(TRUE);
}

int ComplexAssignmentStatement::getIsPostAssignment() const
{
   return(mIsPostAssignment);
}

ostream &ComplexAssignmentStatement::print(ostream &out) const
{
   out << mName << " = ";
   mPtr->print(out);
   return(out);
}
