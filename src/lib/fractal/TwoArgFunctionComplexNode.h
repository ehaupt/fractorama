#ifndef _TWO_ARG_FUNCTION_COMPLEX_NODE_H_
#   define _TWO_ARG_FUNCTION_COMPLEX_NODE_H_

#include "ComplexNode.h"

#ifdef __SUNPRO_CC

typedef dcomplex (*TwoArgFunctionComplexPointer)(
   const dcomplex arg1,
   const dcomplex arg2
);

#else

typedef dcomplex (*TwoArgFunctionComplexPointer)(
   const dcomplex &arg1,
   const dcomplex &arg2
);

#endif

class TwoArgFunctionComplexNode : public ComplexNode
{
   public:
      TwoArgFunctionComplexNode(
         const char *name,
         TwoArgFunctionComplexPointer ptr,
         const ComplexNode *firstPtr,
         const ComplexNode *secondPtr
      );

      ~TwoArgFunctionComplexNode();

      dcomplex evaluate() const;

      ostream &print(ostream &out) const;

      static TwoArgFunctionComplexPointer lookup(const char *name);

   private:
      TwoArgFunctionComplexNode(
         const TwoArgFunctionComplexNode &other
      );

      TwoArgFunctionComplexNode &operator<<(
         const TwoArgFunctionComplexNode &other
      );

      char *mName;
      TwoArgFunctionComplexPointer mPtr;
      const ComplexNode *mFirstPtr;
      const ComplexNode *mSecondPtr;
};

#endif
