#ifndef _DOUBLE_NODE_H_
#   define _DOUBLE_NODE_H_

#include <iostream>

using std::ostream;

#define RND(x) ((x) >= 0.0 ? (int)((x) + 0.5) : (int)((x) - 0.5))

class DoubleNode
{
   public:
      DoubleNode();
      virtual ~DoubleNode();

      virtual double evaluate() const = 0;

      virtual ostream &print(ostream &out) const = 0;

  private:
      DoubleNode(const DoubleNode &);
      DoubleNode &operator=(const DoubleNode &);
};

ostream &operator<<(ostream &out, const DoubleNode &n);

#endif
