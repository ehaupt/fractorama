#include "TernaryDoubleNode.h"
#include "BooleanNode.h"
#include "dmemory.h"

TernaryDoubleNode::TernaryDoubleNode(
   const BooleanNode *testPtr,
   const DoubleNode  *firstPtr,
   const DoubleNode  *secondPtr
)  :
   mTestPtr(testPtr),
   mFirstPtr(firstPtr),
   mSecondPtr(secondPtr)
{
}

TernaryDoubleNode::~TernaryDoubleNode()
{
   DDELETE(mTestPtr);
   DDELETE(mFirstPtr);
   DDELETE(mSecondPtr);
}

double TernaryDoubleNode::evaluate() const
{
   return(
      mTestPtr->evaluate() ?
      mFirstPtr->evaluate() :
      mSecondPtr->evaluate()
   );
}

ostream &TernaryDoubleNode::print(ostream &out) const
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
