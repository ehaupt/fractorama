#ifndef _VARIABLE_DOUBLE_NODE_H_
#   define _VARIABLE_DOUBLE_NODE_H_

#include "DoubleNode.h"

class VariableDoubleNode : public DoubleNode
{
   public:
      VariableDoubleNode(char *name, const double *ptr);
      ~VariableDoubleNode();

      double evaluate() const
      {
         return(*mPtr);
      }

      ostream &print(ostream &out) const;

   private:
      VariableDoubleNode(const VariableDoubleNode &);
      VariableDoubleNode &operator=(const VariableDoubleNode &);
      char *mName;
      const double *mPtr;
};
#endif
