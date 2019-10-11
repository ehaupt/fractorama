#ifndef _COMPLEX_NODE_STACK_H_
#   define _COMPLEX_NODE_STACK_H_

#include "GenericStack.h"
#include "ComplexNode.h"

class ComplexNodeStack
{
   public:
      int isEmpty() const;
      void push(const ComplexNode *ptr);
      const ComplexNode *pop();
      const ComplexNode *top();

   private:
      GenericStack mStack;
};

#endif
