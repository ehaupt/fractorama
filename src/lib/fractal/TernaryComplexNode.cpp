#include "TernaryComplexNode.h"
#include "BooleanNode.h"
#include "dmemory.h"

TernaryComplexNode::TernaryComplexNode(
   const BooleanNode *testPtr,
   const ComplexNode  *firstPtr,
   const ComplexNode  *secondPtr
)  :
   mTestPtr(testPtr),
   mFirstPtr(firstPtr),
   mSecondPtr(secondPtr)
{
}

TernaryComplexNode::~TernaryComplexNode()
{
   DDELETE(mTestPtr);
   DDELETE(mFirstPtr);
   DDELETE(mSecondPtr);
}

dcomplex TernaryComplexNode::evaluate() const
{
   return(
      mTestPtr->evaluate() ?
      mFirstPtr->evaluate() :
      mSecondPtr->evaluate()
   );
}

ostream &TernaryComplexNode::print(ostream &out) const
{
   out << "(";
   mTestPtr->print(out);
   out << " ? ";
   mFirstPtr->print(out);
   out << " : ";
   mSecondPtr->print(out);
   out << ")";

   return(out);
}
