#ifndef _VARIABLE_COMPLEX_NODE_H_
#   define _VARIABLE_COMPLEX_NODE_H_

#include "ComplexNode.h"

class VariableComplexNode : public ComplexNode
{
   public:
      VariableComplexNode(char *name, dcomplex *ptr);
      ~VariableComplexNode();

      dcomplex VariableComplexNode::evaluate() const
      {
         return(*mPtr);
      }

      ostream &print(ostream &out) const;

   private:
      VariableComplexNode(const VariableComplexNode &);
      VariableComplexNode &operator=(const VariableComplexNode &);
      char *mName;
      dcomplex *mPtr;
};
#endif
