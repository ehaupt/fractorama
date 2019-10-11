#ifndef _ATTRIBUTE_DOUBLE_NODE_H_
#   define _ATTRIBUTE_DOUBLE_NODE_H_

#include "DoubleNode.h"
#include "dcomplex.h"

class ComplexNode;

typedef double (*AttributeFunctionPointer)(dcomplex value);

class AttributeDoubleNode : public DoubleNode
{
   public:

      static AttributeDoubleNode *create(
         char *methodName,
         const ComplexNode *node
      );

      ~AttributeDoubleNode();

      double evaluate() const;

      ostream &print(ostream &out) const;

      static const double PI;
      static const double PI_OVER_TWO;
      static const double THREE_PI_OVER_TWO;
      static const double TWO_PI;
      static const double DEGREES_PER_RADIAN;

      static double degrees(dcomplex value);
      static double old_degrees(dcomplex value);
      static double radians(dcomplex value);
      static double old_radians(dcomplex value);
      static double real(dcomplex value);
      static double imaginary(dcomplex value);
      static double magnitude(dcomplex value);
      static double sum_of_squares(dcomplex value);

   private:

#ifdef __GNUC__
      friend class PacifyGPlusPlus;
#endif

      AttributeDoubleNode(
         char *methodName,
         AttributeFunctionPointer ptr,
         const ComplexNode *node
      );

      static AttributeFunctionPointer lookup(char *name);

      AttributeDoubleNode(const AttributeDoubleNode &other);
      AttributeDoubleNode &operator=(const AttributeDoubleNode &other);

      char *mMethodName;
      AttributeFunctionPointer mPtr;
      const ComplexNode *mNode;
};

#endif
