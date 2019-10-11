#ifndef _COLOR_STACK_H_
#   define _COLOR_STACK_H_

#include "GenericStack.h"

class ColorStack
{
   public:
      int isEmpty() const;
      void push(const int *ptr);
      const int *pop();

   private:
      GenericStack mStack;
   
};

#endif
