#ifndef _MAP_COLOR_FUNCTION_DOUBLE_NODE_STACK_H_
#   define _MAP_COLOR_FUNCTION_DOUBLE_NODE_STACK_H_

#include "GenericStack.h"
#include "MapColorFunctionDoubleNode.h"

class MapColorFunctionDoubleNodeStack
{
   public:
      int isEmpty() const;
      int size() const;
      void push(const MapColorFunctionDoubleNode *ptr);
      const MapColorFunctionDoubleNode *pop();
      MapColorFunctionDoubleNode *top();

   private:
      GenericStack mStack;
};

#endif
