#ifndef _ONE_ARG_FUNCTION_DOUBLE_NODE_H_
#   define _ONE_ARG_FUNCTION_DOUBLE_NODE_H_

#include "DoubleNode.h"

typedef double (*OneArgFunctionDoublePointer)(double arg);

class OneArgFunctionDoubleNode : public DoubleNode
{
   public:

      // OneArgFunctionDoubleNode assumes ownership of <nodePtr> and will
      // delete it upon destruction

      OneArgFunctionDoubleNode(
         char *name,
         OneArgFunctionDoublePointer ptr,
         const DoubleNode *nodePtr
      );

      ~OneArgFunctionDoubleNode();

      double evaluate() const;

      ostream &print(ostream &out) const;

      static OneArgFunctionDoublePointer lookup(char *name);

   private:

      // Disallow copy constructor and assignment operator

      OneArgFunctionDoubleNode(const OneArgFunctionDoubleNode &);
      OneArgFunctionDoubleNode &operator=(const OneArgFunctionDoubleNode &);

      static double asec(double value);
      static double acsc(double value);
      static double acot(double value);

      static double asinh(double value);
      static double acosh(double value);
      static double atanh(double value);

      static double asech(double value);
      static double acsch(double value);
      static double acoth(double value);

      static double cot(double value);
      static double sec(double value);
      static double csc(double value);
      static double coth(double value);
      static double sech(double value);
      static double csch(double value);
      static double factorial(double value);

      static double deg2rad(double degrees);
      static double rad2deg(double radians);

      static double bernoulli(double value);
      static double euler(double value);

      static double bit_not(double value);

      char *mName;
      OneArgFunctionDoublePointer mPtr;
      const DoubleNode *mNodePtr;
};
#endif
