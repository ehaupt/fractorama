#ifndef _DOUBLE_NODE_STACK_H_
#   define _DOUBLE_NODE_STACK_H_

#include "GenericStack.h"
#include "DoubleNode.h"

class DoubleNodeStack
{
   public:
      int isEmpty() const;
      void push(const DoubleNode *ptr);
      const DoubleNode *pop();
      const DoubleNode *top();

   private:
      GenericStack mStack;
};

#endif
