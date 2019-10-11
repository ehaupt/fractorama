// Local Headers

#include "ConditionalBooleanNode.h"
#include "dmemory.h"

ConditionalBooleanNode::ConditionalBooleanNode(
   const BooleanNode *leftPtr,
   Operator op,
   const BooleanNode *rightPtr
)  : mLeftPtr(leftPtr), mOperator(op), mRightPtr(rightPtr) {}

ConditionalBooleanNode::~ConditionalBooleanNode()
{
   DDELETE(mLeftPtr);
   DDELETE(mRightPtr);
}

int ConditionalBooleanNode::evaluate() const
{
   int result = 0;

   if(mOperator == _AND_)
   {
      result = (mLeftPtr->evaluate() && mRightPtr->evaluate());
   }
   else
   {
      result = (mLeftPtr->evaluate() || mRightPtr->evaluate());
   }

   return(result);
}

ostream &ConditionalBooleanNode::print(ostream &out) const
{
   mLeftPtr->print(out);
   out << " " << getOperatorString() << " ";
   mRightPtr->print(out);

   return(out);
}


char *ConditionalBooleanNode::getOperatorString() const
{
   char *ptr = 0;

   switch(mOperator)
   {
      case _AND_: ptr = "&&"; break;
      case _OR_ : ptr = "||"; break;
   }

   return(ptr);
}
