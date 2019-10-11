#ifndef _COMPLEX_NODE_H_
#   define _COMPLEX_NODE_H_

#include "dcomplex.h"

#include <iostream>

using std::ostream;

class ComplexNode
{
   public:
      ComplexNode();
      virtual ~ComplexNode();

      virtual dcomplex evaluate() const = 0;

      virtual ostream &print(ostream &out) const = 0;

  private:
      ComplexNode(const ComplexNode &);
      ComplexNode &operator=(const ComplexNode &);
      int mID;
      static int mCount;
};

ostream &operator<<(ostream &out, const ComplexNode &n);

#endif
