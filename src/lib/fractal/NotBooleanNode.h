#ifndef _NOT_BOOLEAN_NODE_H_
#   define _NOT_BOOLEAN_NODE_H_

#include "BooleanNode.h"

class NotBooleanNode : public BooleanNode
{
   public:

      NotBooleanNode(const BooleanNode *node);
      ~NotBooleanNode();

      int evaluate() const;

      ostream &print(ostream &out) const;

  private:
      NotBooleanNode(const NotBooleanNode &);
      NotBooleanNode &operator=(const NotBooleanNode &);

      const BooleanNode *mNode;
};

#endif
