#include "BinaryDoubleNode.h"
#include "dmemory.h"

BinaryDoubleNode::BinaryDoubleNode(
   const DoubleNode *leftPtr,
   Operator op,
   const DoubleNode *rightPtr
)  : mLeftPtr(leftPtr), mOperator(op), mRightPtr(rightPtr)
{
}

BinaryDoubleNode::~BinaryDoubleNode()
{
   DDELETE(mLeftPtr);
   DDELETE(mRightPtr);
}

double BinaryDoubleNode::evaluate() const
{
   double left  = mLeftPtr->evaluate();
   double right = mRightPtr->evaluate();

   switch(mOperator)
   {
      case _PLUS_    : left += right; break;
      case _MINUS_   : left -= right; break;
      case _MULTIPLY_: left *= right; break;
      case _DIVIDE_  : left /= right; break;
   }

   return(left);
}

ostream &BinaryDoubleNode::print(ostream &out) const
{
   out << "(";
   mLeftPtr->print(out);
   out << ") " << getOperatorString() << " (";
   mRightPtr->print(out);
   out << ")";

   return(out);
}

char *BinaryDoubleNode::getOperatorString() const
{
   char *ptr = 0;

   switch(mOperator)
   {
      case _PLUS_    : ptr = "+"; break;
      case _MINUS_   : ptr = "-"; break;
      case _MULTIPLY_: ptr = "*"; break;
      case _DIVIDE_  : ptr = "/"; break;
   }

   return(ptr);
}
