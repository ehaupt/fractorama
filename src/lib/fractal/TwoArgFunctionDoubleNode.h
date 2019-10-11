#ifndef _TWO_ARG_FUNCTION_DOUBLE_NODE_H_
#   define _TWO_ARG_FUNCTION_DOUBLE_NODE_H_

#include "DoubleNode.h"

typedef double (*TwoArgFunctionDoublePointer)(double arg1, double arg2);

class TwoArgFunctionDoubleNode : public DoubleNode
{
   public:
      TwoArgFunctionDoubleNode(
         const char *name,
         TwoArgFunctionDoublePointer ptr,
         const DoubleNode *firstPtr,
         const DoubleNode *secondPtr
      );

      ~TwoArgFunctionDoubleNode();

      double evaluate() const;

      ostream &print(ostream &out) const;

      static double max(double first, double second);
      static double min(double first, double second);
      static double gamma(double first, double second);
      static double bit_and(double first, double second);
      static double bit_or(double first, double second);
      static double bit_shl(double first, double second);
      static double bit_shr(double first, double second);
      static double bit_xor(double first, double second);

      static TwoArgFunctionDoublePointer lookup(const char *name);

      static const char *MOD;
      static const char *POW;

   private:
      TwoArgFunctionDoubleNode(
         const TwoArgFunctionDoubleNode &other
      );

      TwoArgFunctionDoubleNode &operator<<(
         const TwoArgFunctionDoubleNode &other
      );

      char *mName;
      TwoArgFunctionDoublePointer mPtr;
      const DoubleNode *mFirstPtr;
      const DoubleNode *mSecondPtr;
};

#endif
