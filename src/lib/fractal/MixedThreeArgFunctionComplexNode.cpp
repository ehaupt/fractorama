// C/C++ Headers

#include <string.h>

// Local Headers

#include "MixedThreeArgFunctionComplexNode.h"
#include "AttributeDoubleNode.h"
#include "dmemory.h"

MixedThreeArgFunctionComplexNode::MixedThreeArgFunctionComplexNode(
   const char *name,
   MixedThreeArgFunctionComplexPointer ptr,
   const ComplexNode *firstPtr,
   const ComplexNode *secondPtr,
   const DoubleNode  *thirdPtr
)  :
   mPtr(ptr),
   mFirstPtr(firstPtr),
   mSecondPtr(secondPtr),
   mThirdPtr(thirdPtr)
{
   DNEW(mName, char[strlen(name) + 1]);
   strcpy(mName, name);
}

MixedThreeArgFunctionComplexNode::~MixedThreeArgFunctionComplexNode()
{
   DADELETE(mName);

   DDELETE(mFirstPtr);
   DDELETE(mSecondPtr);
   DDELETE(mThirdPtr);
}

dcomplex MixedThreeArgFunctionComplexNode::evaluate() const
{
   return(
      mPtr(
         mFirstPtr->evaluate(),
         mSecondPtr->evaluate(),
         mThirdPtr->evaluate()
      )
   );
}

ostream &MixedThreeArgFunctionComplexNode::print(ostream &out) const
{
   out << mName << "(";
   mFirstPtr->print(out);
   out << ", ";
   mSecondPtr->print(out);
   out << ", ";
   mThirdPtr->print(out);
   out << ")";

   return(out);
}

static dcomplex rotate(
   const dcomplex &first, const dcomplex &second, const double third
)
{
   // Translate the point to the origin

   dcomplex point = first - second;

   // Now convert second from degrees to radians

   double radians = third / AttributeDoubleNode::DEGREES_PER_RADIAN;

   // Now compute the values for our rotation matrix
   //
   // [ cos theta   - sin theta ]
   // [ sin theta     cos theta ]
   //

   double ct = cos(radians);
   double st = sin(radians);

   // Do the rotation

   double xPoint = __REAL(point);
   double yPoint = __IMAG(point);

   double x = ct * xPoint - st * yPoint;
   double y = st * xPoint + ct * yPoint;

   // Return the rotated point, adding back the original origin

   dcomplex rotated(x + __REAL(second), y + __IMAG(second));

   return(rotated);
}

MixedThreeArgFunctionComplexPointer MixedThreeArgFunctionComplexNode::lookup(
   const char *name
)
{
   struct Table
   {
      MixedThreeArgFunctionComplexPointer ptr;
      const char *name;
   };

   // We've only got one function with the signature: complex, double, complex
   // but use a lookup table anyway in case we ever add subsequent functions

   static Table t[] =
   {
      { rotate, "rotate" }
   };

   int size = sizeof(t) / sizeof(t[0]);

   for(int i = 0; i < size; i ++)
      if(strcmp(t[i].name, name) == 0)
         return(t[i].ptr);

   return(0);
}
