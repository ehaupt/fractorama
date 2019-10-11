#ifndef _COMPLEX_ASSIGNMENT_STATEMENT_H_
#   define _COMPLEX_ASSIGNMENT_STATEMENT_H_

#include "Statement.h"
#include "dcomplex.h"

class ComplexNode;

class ComplexAssignmentStatement : public Statement
{
   public:
      ComplexAssignmentStatement(
         dcomplex *vptr,
         char *name,
         const ComplexNode *ptr,
         int isPostAssignment = FALSE
      );

      ~ComplexAssignmentStatement();

      int execute(
         InfiniteLoopCallback *callback,
         LoopControl *control
      ) const;

      int getIsPostAssignment() const;
      dcomplex *getPointer() const { return(mVPtr); }

      ostream &print(ostream &out) const;

   private:
      dcomplex *mVPtr;
      char *mName;
      const ComplexNode *mPtr;
      int mIsPostAssignment;
};
#endif
