// Local Headers

#include "RelationalBooleanNode.h"
#include "dmemory.h"

RelationalBooleanNode::RelationalBooleanNode(
   const DoubleNode *leftPtr,
   Operator op,
   const DoubleNode *rightPtr
)  : mLeftPtr(leftPtr), mOperator(op), mRightPtr(rightPtr) {}

RelationalBooleanNode::~RelationalBooleanNode()
{
   DDELETE(mLeftPtr);
   DDELETE(mRightPtr);
}

int RelationalBooleanNode::evaluate() const
{
   double left  = mLeftPtr->evaluate();
   double right = mRightPtr->evaluate();
   int result   = 0;

   switch(mOperator)
   {
      case _LT_: result = left < right;  break;
      case _GT_: result = left > right;  break;
      case _LE_: result = left <= right; break;
      case _GE_: result = left >= right; break;
      case _EQ_: result = left == right; break;
      case _NE_: result = left != right; break;
   }

   return(result);
}

ostream &RelationalBooleanNode::print(ostream &out) const
{
   mLeftPtr->print(out);
   out << " " << getOperatorString() << " ";
   mRightPtr->print(out);

   return(out);
}

char *RelationalBooleanNode::getOperatorString() const
{
   char *ptr = 0;

   switch(mOperator)
   {
      case _LT_: ptr = "<";  break;
      case _GT_: ptr = ">";  break;
      case _LE_: ptr = "<="; break;
      case _GE_: ptr = ">="; break;
      case _EQ_: ptr = "=="; break;
      case _NE_: ptr = "!="; break;
   }

   return(ptr);
}
