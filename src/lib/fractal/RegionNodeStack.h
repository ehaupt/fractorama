#ifndef _REGION_NODE_STACK_H_
#   define _REGION_NODE_STACK_H_

#include "GenericStack.h"
#include "RegionNode.h"

class RegionNodeStack
{
   public:
      int isEmpty() const;
      void push(const RegionNode *ptr);
      const RegionNode *pop();

   private:
      GenericStack mStack;
};

#endif
