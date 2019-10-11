#ifndef _TRUE_BOOLEAN_NODE_H_
#   define _TRUE_BOOLEAN_NODE_H_

#include "BooleanNode.h"
#include "DoubleNode.h"

class TrueBooleanNode : public BooleanNode
{
   public:

      TrueBooleanNode();
      ~TrueBooleanNode();

      int evaluate() const;

      ostream &print(ostream &out) const;

  private:
      TrueBooleanNode(const TrueBooleanNode &);
      TrueBooleanNode &operator=(const TrueBooleanNode &);
};

#endif
