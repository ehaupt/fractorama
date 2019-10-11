// Local Headers

#include "AssignmentDoubleNode.h"
#include "DoubleAssignmentStatement.h"
#include "dmemory.h"

AssignmentDoubleNode::AssignmentDoubleNode(
   const DoubleAssignmentStatement *statement
) :
   mStatement(statement),
   mIsPostAssignment(mStatement->getIsPostAssignment())
{
}

AssignmentDoubleNode::~AssignmentDoubleNode()
{
   DDELETE(mStatement);
}

double AssignmentDoubleNode::evaluate() const
{
   double value = 0.0;

   if(mIsPostAssignment)
      value = *mStatement->getPointer();

   mStatement->execute(NULL, NULL);

   if(!mIsPostAssignment)
      value = *mStatement->getPointer();

   return(value);
}

ostream &AssignmentDoubleNode::print(ostream &out) const
{
   out << "(";
   mStatement->print(out);
   return(out << ")");
}
