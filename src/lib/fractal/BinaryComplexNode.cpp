// Local Headers

#include "BinaryComplexNode.h"
#include "dmemory.h"

BinaryComplexNode::BinaryComplexNode(
   const ComplexNode *leftPtr,
   Operator op,
   const ComplexNode *rightPtr
)  : mLeftPtr(leftPtr), mOperator(op), mRightPtr(rightPtr)
{
}

BinaryComplexNode::~BinaryComplexNode()
{
   DDELETE(mLeftPtr);
   DDELETE(mRightPtr);
}

dcomplex BinaryComplexNode::evaluate() const
{
   dcomplex left  = mLeftPtr->evaluate();
   dcomplex right = mRightPtr->evaluate();

   switch(mOperator)
   {
      case _PLUS_    : left += right; break;
      case _MINUS_   : left -= right; break;
      case _MULTIPLY_: left *= right; break;
      case _DIVIDE_  : left /= right; break;
   }

   return(left);
}

ostream &BinaryComplexNode::print(ostream &out) const
{
   out << "(";
   mLeftPtr->print(out);
   out << ") " << getOperatorString() << " (";
   mRightPtr->print(out);
   out << ")";

   return(out);
}

char *BinaryComplexNode::getOperatorString() const
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
