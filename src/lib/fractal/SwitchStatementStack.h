#ifndef _SWITCH_STATEMENT_STACK_H_
#   define _SWITCH_STATEMENT_STACK_H_

#include "GenericStack.h"

class SwitchStatement;

class SwitchStatementStack
{
   public:
      void push(const SwitchStatement *ptr);
      const SwitchStatement *pop();
      SwitchStatement *top();
    
   private:
      GenericStack mStack;
};

#endif
