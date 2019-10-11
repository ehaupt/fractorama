// C/C++ Headers

#include <string.h>

#ifdef _WIN32
#   include <float.h>
#   define ISNAN(x) _isnan(x)
#else
#   include <math.h>
#   define ISNAN(x) isnan(x)
#endif

// Local Headers

#include "DoubleAssignmentStatement.h"
#include "DoubleVariables.h"
#include "DoubleNode.h"
#include "dmemory.h"

DoubleAssignmentStatement::DoubleAssignmentStatement(
   double *vptr,
   char *name,
   const DoubleNode *ptr,
   int isPostAssignment
) :
   mVPtr(vptr),
   mName(0),
   mPtr(ptr),
   mIsPostAssignment(isPostAssignment)
{
   DNEW(mName, char[strlen(name) + 1]);
   strcpy(mName, name);
}

DoubleAssignmentStatement::~DoubleAssignmentStatement()
{
   DADELETE(mName);
   DDELETE(mPtr);
}

int DoubleAssignmentStatement::execute(
   InfiniteLoopCallback *, LoopControl *
) const
{
   double value = mPtr->evaluate();

   // The use of 'ISNAN' here is necessary to enforce uniform
   // behavior between win32 and linux.  On linux, a value that
   // is not-a-number ends up being stored as a zero but
   // that wasn't what I was seeing on win32 hence the
   // check below.

   *mVPtr = (ISNAN(value) ? DoubleVariables::ZERO : value);

   return(TRUE);
}

int DoubleAssignmentStatement::getIsPostAssignment() const
{
   return(mIsPostAssignment);
}

ostream &DoubleAssignmentStatement::print(ostream &out) const
{
   out << "$" << mName << " = ";
   mPtr->print(out);
   return(out);
}
