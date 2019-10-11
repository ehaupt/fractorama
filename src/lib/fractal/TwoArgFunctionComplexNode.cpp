// C/C++ Headers

#include <string.h>

// Local Headers

#include "TwoArgFunctionComplexNode.h"
#include "TwoArgFunctionDoubleNode.h"
#include "ComplexVariables.h"
#include "dmemory.h"

TwoArgFunctionComplexNode::TwoArgFunctionComplexNode(
   const char *name,
   TwoArgFunctionComplexPointer ptr,
   const ComplexNode *firstPtr,
   const ComplexNode *secondPtr
)  : mPtr(ptr), mFirstPtr(firstPtr), mSecondPtr(secondPtr)
{
   DNEW(mName, char[strlen(name) + 1]);
   strcpy(mName, name);
}

TwoArgFunctionComplexNode::~TwoArgFunctionComplexNode()
{
   DADELETE(mName);

   DDELETE(mFirstPtr);
   DDELETE(mSecondPtr);
}

dcomplex TwoArgFunctionComplexNode::evaluate() const
{
   return(
      mPtr(
         mFirstPtr->evaluate(),
         mSecondPtr->evaluate()
      )
   );
}

ostream &TwoArgFunctionComplexNode::print(ostream &out) const
{
   out << mName << "(";
   mFirstPtr->print(out);
   out << ", ";
   mSecondPtr->print(out);
   out << ")";

   return(out);
}

static dcomplex power(const dcomplex &first, const dcomplex &second)
{
   // Originally, we just used STD(pow) but in a case like this:
   //
   // pow(a, b)
   //
   // when a is [0, 0] the result would be (nan, nan) since
   //
   // pow(a, b) => exp(b * log(a)) and log([0, 0]) is undefined
   //
   // Anyway, now we just do a quick check against zero which allows
   // us to get the same results from:
   //
   // z = z * z + c;
   // z = pow(z, 2) + c;
   // z = z ^ 2 + c;
   //
   // when z takes on the value [0, 0]

   if(first == ComplexVariables::ZERO)
      return(ComplexVariables::ZERO);

   return(STD(pow)(first, second));
}

TwoArgFunctionComplexPointer TwoArgFunctionComplexNode::lookup(
   const char *name
)
{
   struct Table
   {
      TwoArgFunctionComplexPointer ptr;
      const char *name;
   };

   // Instead of STD(pow) we use our own 'power' function, see that
   // function above for an explanation

   static Table t[] =
   {
      { power, TwoArgFunctionDoubleNode::POW }
   };

   int size = sizeof(t) / sizeof(t[0]);

   for(int i = 0; i < size; i ++)
      if(strcmp(t[i].name, name) == 0)
         return(t[i].ptr);

   return(0);
}
