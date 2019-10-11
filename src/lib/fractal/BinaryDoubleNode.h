#ifndef _BINARY_DOUBLE_NODE_H_
#   define _BINARY_DOUBLE_NODE_H_

#include "DoubleNode.h"

class BinaryDoubleNode : public DoubleNode
{
   public:

      typedef enum { _PLUS_, _MINUS_, _MULTIPLY_, _DIVIDE_ } Operator;

      BinaryDoubleNode(
         const DoubleNode *leftPtr,
         Operator op,
         const DoubleNode *rightPtr
      );

      ~BinaryDoubleNode();

      double evaluate() const;

      ostream &print(ostream &out) const;

   private:
      BinaryDoubleNode(const BinaryDoubleNode &other);

      BinaryDoubleNode &operator<<(const BinaryDoubleNode &other);

      char *getOperatorString() const;
      const DoubleNode *mLeftPtr;
      const Operator mOperator;
      const DoubleNode *mRightPtr;
};

#endif
