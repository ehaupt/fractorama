#ifndef _CONDITIONAL_STATEMENT_H_
#   define _CONDITIONAL_STATEMENT_H_

#include "Statement.h"

class BooleanNode;

class ConditionalStatement : public Statement
{
   public:
      ConditionalStatement(
         const Statement   **statements,
         const BooleanNode **conditions,
         int count,
         const Statement *elseStatement = 0
      );

      ~ConditionalStatement();

      int execute(
         InfiniteLoopCallback *callback,
         LoopControl *control
      ) const;

      ostream &print(ostream &out) const;

   private:
      const Statement   **mStatements;
      const BooleanNode **mConditions;
      int mCount;
      const Statement *mElse;
};
#endif
