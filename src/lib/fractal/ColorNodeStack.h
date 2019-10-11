#ifndef _COLOR_NODE_STACK_H_
#   define _COLOR_NODE_STACK_H_

#include "GenericStack.h"
#include "ColorNode.h"

class ColorNodeStack
{
   public:
      int isEmpty() const;
      void push(const ColorNode *ptr);
      const ColorNode *pop();

   private:
      GenericStack mStack;
   
};

#endif
