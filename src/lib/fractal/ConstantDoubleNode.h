#ifndef _CONSTANT_DOUBLE_NODE_H_
#   define _CONSTANT_DOUBLE_NODE_H_

#include "DoubleNode.h"

class ConstantDoubleNode : public DoubleNode
{
   public:
      ConstantDoubleNode(double value);

      double evaluate() const;

      ostream &print(ostream &out) const;

  private:
      ConstantDoubleNode(const ConstantDoubleNode &);
      ConstantDoubleNode &operator=(const ConstantDoubleNode &);
      double mValue;
};

#endif
