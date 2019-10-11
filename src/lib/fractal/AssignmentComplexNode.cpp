// Local Headers

#include "AssignmentComplexNode.h"
#include "ComplexAssignmentStatement.h"
#include "dmemory.h"

AssignmentComplexNode::AssignmentComplexNode(
   const ComplexAssignmentStatement *statement
) :
   mStatement(statement),
   mIsPostAssignment(mStatement->getIsPostAssignment())
{
}

AssignmentComplexNode::~AssignmentComplexNode()
{
   DDELETE(mStatement);
}

dcomplex AssignmentComplexNode::evaluate() const
{
   dcomplex value;

   if(mIsPostAssignment)
      value = *mStatement->getPointer();

   mStatement->execute(NULL, NULL);

   if(!mIsPostAssignment)
      value = *mStatement->getPointer();

   return(value);
}

ostream &AssignmentComplexNode::print(ostream &out) const
{
   out << "(";
   mStatement->print(out);
   return(out << ")");
}
