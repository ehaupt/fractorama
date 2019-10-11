#ifndef _BINARY_COMPLEX_NODE_H_
#   define _BINARY_COMPLEX_NODE_H_

#include "ComplexNode.h"

class BinaryComplexNode : public ComplexNode
{
   public:

      typedef enum { _PLUS_, _MINUS_, _MULTIPLY_, _DIVIDE_ } Operator;

      BinaryComplexNode(
         const ComplexNode *leftPtr,
         Operator op,
         const ComplexNode *rightPtr
      );

      ~BinaryComplexNode();

      dcomplex evaluate() const;

      ostream &print(ostream &out) const;

   private:
      BinaryComplexNode(const BinaryComplexNode &other);

      BinaryComplexNode &operator<<(const BinaryComplexNode &other);

      char *getOperatorString() const;
      const ComplexNode *mLeftPtr;
      const Operator mOperator;
      const ComplexNode *mRightPtr;
};

#endif
