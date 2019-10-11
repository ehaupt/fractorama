#ifndef _COMPOUND_STATEMENT_STACK_H_
#   define _COMPOUND_STATEMENT_STACK_H_

#include "GenericStack.h"

class CompoundStatement;

class CompoundStatementStack
{
   public:
      int isEmpty() const;
      int size() const;
      void push(const CompoundStatement *ptr);
      const CompoundStatement *pop();
      CompoundStatement *top();
    
   private:
      GenericStack mStack;
};

#endif
