#ifndef _FLAG_STACK_H_
#   define _FLAG_STACK_H_

#include "GenericStack.h"

class FlagStack
{
   public:
      int isEmpty() const;
      void push(int value);
      const int top();
      const int pop();

   private:
      GenericStack mStack;
   
};

#endif
