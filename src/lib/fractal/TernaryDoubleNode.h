#ifndef _TERNARY_DOUBLE_NODE_H_
#   define _TERNARY_DOUBLE_NODE_H_

#include "DoubleNode.h"

class BooleanNode;

class TernaryDoubleNode : public DoubleNode
{
   public:

      TernaryDoubleNode(
         const BooleanNode *testPtr,
         const DoubleNode *firstPtr,
         const DoubleNode *secondPtr
      );

      ~TernaryDoubleNode();

      double evaluate() const;

      ostream &print(ostream &out) const;

   private:
      TernaryDoubleNode(const TernaryDoubleNode &other);

      TernaryDoubleNode &operator<<(const TernaryDoubleNode &other);

      const BooleanNode *mTestPtr;
      const DoubleNode  *mFirstPtr;
      const DoubleNode  *mSecondPtr;
};

#endif
