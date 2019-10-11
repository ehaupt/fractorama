#ifndef _ASSIGNMENT_COMPLEX_NODE_H_
#   define _ASSIGNMENT_COMPLEX_NODE_H_

#include "ComplexNode.h"

class ComplexAssignmentStatement;

class AssignmentComplexNode : public ComplexNode
{
   public:
      AssignmentComplexNode(
         const ComplexAssignmentStatement *statement
      );

      ~AssignmentComplexNode();

      dcomplex evaluate() const;

      ostream &print(ostream &out) const;

  private:
      AssignmentComplexNode(const AssignmentComplexNode &);
      AssignmentComplexNode &operator=(const AssignmentComplexNode &);
      const ComplexAssignmentStatement *mStatement;
      int mIsPostAssignment;
};

#endif
