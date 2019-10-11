#ifndef _DOUBLE_ASSIGNMENT_STATEMENT_H_
#   define _DOUBLE_ASSIGNMENT_STATEMENT_H_

#include "Statement.h"

class DoubleNode;

class DoubleAssignmentStatement : public Statement
{
   public:
      DoubleAssignmentStatement(
         double *vptr,
         char *name,
         const DoubleNode *ptr,
         int isPostAssignment = FALSE
      );

      ~DoubleAssignmentStatement();

      int execute(
         InfiniteLoopCallback *callback,
         LoopControl *control
      ) const;

      int getIsPostAssignment() const;
      double *getPointer() const { return(mVPtr); }

      ostream &print(ostream &out) const;

   private:
      double *mVPtr;
      char *mName;
      const DoubleNode *mPtr;
      int mIsPostAssignment;
};
#endif
