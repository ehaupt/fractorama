#ifndef _FALSE_BOOLEAN_NODE_H_
#   define _FALSE_BOOLEAN_NODE_H_

#include "BooleanNode.h"

class FalseBooleanNode : public BooleanNode
{
   public:

      FalseBooleanNode();
      ~FalseBooleanNode();

      int evaluate() const;

      ostream &print(ostream &out) const;

  private:
      FalseBooleanNode(const FalseBooleanNode &);
      FalseBooleanNode &operator=(const FalseBooleanNode &);
};

#endif
