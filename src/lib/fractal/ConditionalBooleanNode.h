#ifndef _CONDITIONAL_BOOLEAN_NODE_H_
#   define _CONDITIONAL_BOOLEAN_NODE_H_

#include "BooleanNode.h"

class ConditionalBooleanNode : public BooleanNode
{
   public:

      typedef enum { _AND_, _OR_ } Operator;

      ConditionalBooleanNode(
         const BooleanNode *leftPtr,
         Operator op,
         const BooleanNode *rightPtr
      );

      ~ConditionalBooleanNode();

      int evaluate() const;

      ostream &print(ostream &out) const;

  private:
      ConditionalBooleanNode(const ConditionalBooleanNode &);
      ConditionalBooleanNode &operator=(const ConditionalBooleanNode &);
      char *getOperatorString() const;
      const BooleanNode *mLeftPtr;
      Operator mOperator;
      const BooleanNode *mRightPtr;
};

#endif
