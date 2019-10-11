#ifndef _MAP_COLOR_FUNCTION_DOUBLE_NODE_H_
#   define _MAP_COLOR_FUNCTION_DOUBLE_NODE_H_

#include "DoubleNode.h"

class MapColorFunctionDoubleNode : public DoubleNode
{
   public:

      MapColorFunctionDoubleNode();
      ~MapColorFunctionDoubleNode();

      double evaluate() const;

      int size() const;

      void addArgument(const DoubleNode *arg);

      ostream &print(ostream &out) const;

   private:

      // Disallow copy constructor and assignment operator

      MapColorFunctionDoubleNode(const MapColorFunctionDoubleNode &);
      MapColorFunctionDoubleNode &operator=(const MapColorFunctionDoubleNode &);

      const DoubleNode **mArgs;
      int mArgCount;
};
#endif
