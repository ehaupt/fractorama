#ifndef _ASSIGNMENT_DOUBLE_NODE_H_
#   define _ASSIGNMENT_DOUBLE_NODE_H_

#include "DoubleNode.h"

class DoubleAssignmentStatement;

class AssignmentDoubleNode : public DoubleNode
{
   public:
      AssignmentDoubleNode(
         const DoubleAssignmentStatement *statement
      );

      ~AssignmentDoubleNode();

      double evaluate() const;

      ostream &print(ostream &out) const;

  private:
      AssignmentDoubleNode(const AssignmentDoubleNode &);
      AssignmentDoubleNode &operator=(const AssignmentDoubleNode &);
      const DoubleAssignmentStatement *mStatement;
      int mIsPostAssignment;
};

#endif
