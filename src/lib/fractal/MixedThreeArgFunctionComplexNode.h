#ifndef _MIXED_THREE_ARG_FUNCTION_COMPLEX_NODE_H_
#   define _MIXED_THREE_ARG_FUNCTION_COMPLEX_NODE_H_

#include "ComplexNode.h"

#ifdef __SUNPRO_CC

typedef dcomplex (*MixedThreeArgFunctionComplexPointer)(
   const dcomplex arg1,
   const dcomplex arg2,
   const double   arg3
);

#else

typedef dcomplex (*MixedThreeArgFunctionComplexPointer)(
   const dcomplex &arg1,
   const dcomplex &arg2,
   const double    arg3
);

#endif

class DoubleNode;

class MixedThreeArgFunctionComplexNode : public ComplexNode
{
   public:
      MixedThreeArgFunctionComplexNode(
         const char *name,
         MixedThreeArgFunctionComplexPointer ptr,
         const ComplexNode *firstPtr,
         const ComplexNode *secondPtr,
         const DoubleNode  *thirdPtr
      );

      ~MixedThreeArgFunctionComplexNode();

      dcomplex evaluate() const;

      ostream &print(ostream &out) const;

      static MixedThreeArgFunctionComplexPointer lookup(const char *name);

   private:
      MixedThreeArgFunctionComplexNode(
         const MixedThreeArgFunctionComplexNode &other
      );

      MixedThreeArgFunctionComplexNode &operator<<(
         const MixedThreeArgFunctionComplexNode &other
      );

      char *mName;
      MixedThreeArgFunctionComplexPointer mPtr;
      const ComplexNode *mFirstPtr;
      const ComplexNode *mSecondPtr;
      const DoubleNode *mThirdPtr;
};

#endif
