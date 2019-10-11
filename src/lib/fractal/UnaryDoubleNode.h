#ifndef _UNARY_DOUBLE_NODE_H_
#   define _UNARY_DOUBLE_NODE_H_

#include "DoubleNode.h"

class UnaryDoubleNode : public DoubleNode
{
   public:
      UnaryDoubleNode(const DoubleNode *nodePtr);
      ~UnaryDoubleNode();

      double evaluate() const;

      ostream &print(ostream &out) const;

  private:
      UnaryDoubleNode(const UnaryDoubleNode &);
      UnaryDoubleNode &operator=(const UnaryDoubleNode &);
      const DoubleNode *mNodePtr;
};

#endif
