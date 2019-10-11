#ifndef _TERNARY_COMPLEX_NODE_H_
#   define _TERNARY_COMPLEX_NODE_H_

#include "ComplexNode.h"

class BooleanNode;

class TernaryComplexNode : public ComplexNode
{
   public:

      TernaryComplexNode(
         const BooleanNode *testPtr,
         const ComplexNode *firstPtr,
         const ComplexNode *secondPtr
      );

      ~TernaryComplexNode();

      dcomplex evaluate() const;

      ostream &print(ostream &out) const;

   private:
      TernaryComplexNode(const TernaryComplexNode &other);

      TernaryComplexNode &operator<<(const TernaryComplexNode &other);

      const BooleanNode *mTestPtr;
      const ComplexNode  *mFirstPtr;
      const ComplexNode  *mSecondPtr;
};

#endif
