#ifndef _UNARY_COMPLEX_NODE_H_
#   define _UNARY_COMPLEX_NODE_H_

#include "ComplexNode.h"

class UnaryComplexNode : public ComplexNode
{
   public:
      // UnaryComplexNode assumes ownership of <nodePtr> and will
      // delete it upon destruction

      UnaryComplexNode(const ComplexNode *nodePtr);

      ~UnaryComplexNode();

      dcomplex evaluate() const;

      ostream &print(ostream &out) const;

   private:

      // Disallow copy construction and assignment

      UnaryComplexNode(const UnaryComplexNode &);
      UnaryComplexNode &operator=(const UnaryComplexNode &);
      const ComplexNode *mComplexNodePtr;
};
#endif
