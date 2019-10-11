#ifndef _FOR_STATEMENT_H_
#   define _FOR_STATEMENT_H_

#include "Statement.h"

class BooleanNode;

class ForStatement : public Statement
{
   public:
      ForStatement(
         const Statement   *initializeStatement,
         const BooleanNode *condition,
         const Statement   *incrementStatement,
         const Statement   *bodyStatement
      );

      ~ForStatement();

      int execute(
         InfiniteLoopCallback *callback,
         LoopControl *control
      )  const;

      ostream &print(ostream &out) const;

   private:
      const Statement   *mInitializeStatement;
      const BooleanNode *mCondition;
      const Statement   *mIncrementStatement;
      const Statement   *mBodyStatement;
};
#endif
