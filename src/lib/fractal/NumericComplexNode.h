#ifndef _NUMERIC_COMPLEX_NODE_H_
#   define _NUMERIC_COMPLEX_NODE_H_

#include "ComplexNode.h"

class DoubleNode;

class NumericComplexNode : public ComplexNode
{
   public:
      NumericComplexNode(
         const DoubleNode *realPart,
         const DoubleNode *imaginaryPart = 0
      );

      ~NumericComplexNode();

      dcomplex evaluate() const;

      ostream &print(ostream &out) const;

   private:
      NumericComplexNode(const NumericComplexNode &);
      NumericComplexNode &operator=(const NumericComplexNode &);
      const DoubleNode *mReal;
      const DoubleNode *mImaginary;
};
#endif
