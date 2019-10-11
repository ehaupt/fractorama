#ifndef _ONE_ARG_FUNCTION_COMPLEX_NODE_H_
#   define _ONE_ARG_FUNCTION_COMPLEX_NODE_H_

#include "ComplexNode.h"

#ifdef __SUNPRO_CC

typedef dcomplex (*OneArgFunctionComplexPointer)(
   const dcomplex arg
);

#else

typedef dcomplex (*OneArgFunctionComplexPointer)(
   const dcomplex &arg
);

#endif

class OneArgFunctionComplexNode : public ComplexNode
{
   public:

      // OneArgFunctionComplexNode assumes ownership of <nodePtr> and will
      // delete it upon destruction

      OneArgFunctionComplexNode(
         char *name,
         OneArgFunctionComplexPointer ptr,
         const ComplexNode *nodePtr
      );

      ~OneArgFunctionComplexNode();

      dcomplex evaluate() const;

      ostream &print(ostream &out) const;

      static OneArgFunctionComplexPointer lookup(char *name);

   private:

      // Disallow copy constructor and assignment operator

      OneArgFunctionComplexNode(const OneArgFunctionComplexNode &);
      OneArgFunctionComplexNode &operator=(const OneArgFunctionComplexNode &);

      static const dcomplex I;
      static const dcomplex MINUS_I;
      static const dcomplex I_OVER_2;

      static dcomplex asin(const dcomplex &value);
      static dcomplex acos(const dcomplex &value);
      static dcomplex atan(const dcomplex &value);

      static dcomplex asec(const dcomplex &value);
      static dcomplex acsc(const dcomplex &value);
      static dcomplex acot(const dcomplex &value);

      static dcomplex asinh(const dcomplex &value);
      static dcomplex acosh(const dcomplex &value);
      static dcomplex atanh(const dcomplex &value);

      static dcomplex asech(const dcomplex &value);
      static dcomplex acsch(const dcomplex &value);
      static dcomplex acoth(const dcomplex &value);

      static dcomplex tan(const dcomplex &value);
      static dcomplex cot(const dcomplex &value);
      static dcomplex sec(const dcomplex &value);
      static dcomplex csc(const dcomplex &value);

      static dcomplex tanh(const dcomplex &value);
      static dcomplex sech(const dcomplex &value);
      static dcomplex csch(const dcomplex &value);
      static dcomplex coth(const dcomplex &value);

      char *mName;
      OneArgFunctionComplexPointer mPtr;
      const ComplexNode *mNodePtr;
};
#endif
