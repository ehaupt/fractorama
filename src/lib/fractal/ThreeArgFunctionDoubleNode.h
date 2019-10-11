#ifndef _THREE_ARG_FUNCTION_DOUBLE_NODE_H_
#   define _THREE_ARG_FUNCTION_DOUBLE_NODE_H_

#include "DoubleNode.h"

typedef double (*ThreeArgFunctionDoublePointer)(
   double arg1, double arg2, double arg3
);

class ThreeArgFunctionDoubleNode : public DoubleNode
{
   public:
      ThreeArgFunctionDoubleNode(
         char *name,
         ThreeArgFunctionDoublePointer ptr,
         const DoubleNode *firstPtr,
         const DoubleNode *secondPtr,
         const DoubleNode *thirdPtr
      );

      ~ThreeArgFunctionDoubleNode();

      double evaluate() const;

      ostream &print(ostream &out) const;

      static ThreeArgFunctionDoublePointer lookup(char *name);

   private:
      ThreeArgFunctionDoubleNode(
         const ThreeArgFunctionDoubleNode &other
      );

      ThreeArgFunctionDoubleNode &operator<<(
         const ThreeArgFunctionDoubleNode &other
      );

      char *mName;
      ThreeArgFunctionDoublePointer mPtr;
      const DoubleNode *mFirstPtr;
      const DoubleNode *mSecondPtr;
      const DoubleNode *mThirdPtr;
};

#endif
