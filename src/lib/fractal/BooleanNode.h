#ifndef _BOOLEAN_NODE_H_
#   define _BOOLEAN_NODE_H_

#include <iostream>

using std::ostream;

class BooleanNode
{
   public:
      BooleanNode();
      virtual ~BooleanNode();

      virtual int evaluate() const = 0;

      virtual ostream &print(ostream &out) const = 0;

  private:
      BooleanNode(const BooleanNode &);
      BooleanNode &operator=(const BooleanNode &);
};

ostream &operator<<(ostream &out, const BooleanNode &n);

#endif
