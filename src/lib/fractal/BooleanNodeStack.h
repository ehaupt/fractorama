#ifndef _BOOLEAN_NODE_STACK_H_
#   define _BOOLEAN_NODE_STACK_H_

#include "GenericStack.h"
#include "BooleanNode.h"

class BooleanNodeStack
{
   public:
      int isEmpty() const;
      int size() const;
      void push(const BooleanNode *ptr);
      const BooleanNode *pop();

   private:
      GenericStack mStack;
};

#endif
