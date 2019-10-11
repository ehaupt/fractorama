#ifndef _RELATIONALL_BOOLEAN_NODE_H_
#   define _RELATIONAL_BOOLEAN_NODE_H_

#include "BooleanNode.h"
#include "DoubleNode.h"

class RelationalBooleanNode : public BooleanNode
{
   public:

      typedef enum { _LT_, _GT_, _LE_, _GE_, _EQ_, _NE_ } Operator;

      RelationalBooleanNode(
         const DoubleNode *leftPtr,
         Operator op,
         const DoubleNode *rightPtr
      );

      ~RelationalBooleanNode();

      int evaluate() const;

      ostream &print(ostream &out) const;

  private:
      RelationalBooleanNode(const RelationalBooleanNode &);
      RelationalBooleanNode &operator=(const RelationalBooleanNode &);
      char *getOperatorString() const;
      const DoubleNode *mLeftPtr;
      Operator mOperator;
      const DoubleNode *mRightPtr;
};

#endif
