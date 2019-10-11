// Local Headers

#include "NumericComplexNode.h"
#include "ConstantDoubleNode.h"
#include "dmemory.h"

NumericComplexNode::NumericComplexNode(
   const DoubleNode *realPart,
   const DoubleNode *imaginaryPart
)  :
   mReal(realPart),
   mImaginary(imaginaryPart)
{
   if(!mImaginary)
      DNEW(mImaginary, ConstantDoubleNode(0.0));
}

NumericComplexNode::~NumericComplexNode()
{
   DDELETE(mReal);
   DDELETE(mImaginary);
}

dcomplex NumericComplexNode::evaluate() const
{
   dcomplex value(
      mReal->evaluate(), mImaginary->evaluate()
   );

   return(value);
}

ostream &NumericComplexNode::print(ostream &out) const
{
   out << "[";
   mReal->print(out);
   out << ", ";
   mImaginary->print(out);
   out << "]";

   return(out);
}
