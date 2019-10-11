// C/C++ Headers

#include <string.h>
#include <math.h>

// Local Headers

#include "TwoArgFunctionDoubleNode.h"
#include "dmemory.h"

const char *TwoArgFunctionDoubleNode::MOD = "mod";
const char *TwoArgFunctionDoubleNode::POW = "pow";

TwoArgFunctionDoubleNode::TwoArgFunctionDoubleNode(
   const char *name,
   TwoArgFunctionDoublePointer ptr,
   const DoubleNode *firstPtr,
   const DoubleNode *secondPtr
)  : mPtr(ptr), mFirstPtr(firstPtr), mSecondPtr(secondPtr)
{
   DNEW(mName, char[strlen(name) + 1]);
   strcpy(mName, name);
}

TwoArgFunctionDoubleNode::~TwoArgFunctionDoubleNode()
{
   DADELETE(mName);
   DDELETE(mFirstPtr);
   DDELETE(mSecondPtr);
}

double TwoArgFunctionDoubleNode::evaluate() const
{
   return(
      mPtr(mFirstPtr->evaluate(), mSecondPtr->evaluate())
   );
}

ostream &TwoArgFunctionDoubleNode::print(ostream &out) const
{
   out << mName << "(";
   mFirstPtr->print(out);
   out << ", ";
   mSecondPtr->print(out);
   out << ")";

   return(out);
}

double TwoArgFunctionDoubleNode::min(double first, double second)
{
   return(first < second ? first : second);
}

double TwoArgFunctionDoubleNode::max(double first, double second)
{
   return(first > second ? first : second);
}

double TwoArgFunctionDoubleNode::gamma(double first, double second)
{
   double result    = 0.0;
   double rgbValue  = (first < 0.0 ? 0.0 : first > 255.0 ? 255 : first);
 
   if(second > 0.0)
   {
      result = 255.0 * pow(rgbValue / 255.0, 1.0 / second);
 
      if(result < 0.0)        result = 0.0;
      else if(result > 255.0) result = 255.0;
   }
   else
   {
      result = rgbValue;
   }
 
   return(result);
}

double TwoArgFunctionDoubleNode::bit_and(double first, double second)
{
   return(RND(first) & RND(second));
}

double TwoArgFunctionDoubleNode::bit_or(double first, double second)
{
   return(RND(first) | RND(second));
}

double TwoArgFunctionDoubleNode::bit_shl(double first, double second)
{
   return(RND(first) << RND(second));
}

double TwoArgFunctionDoubleNode::bit_shr(double first, double second)
{
   return(RND(first) >> RND(second));
}

double TwoArgFunctionDoubleNode::bit_xor(double first, double second)
{
   return(RND(first) ^ RND(second));
}

TwoArgFunctionDoublePointer TwoArgFunctionDoubleNode::lookup(
   const char *name
)
{
   struct Table
   {
      TwoArgFunctionDoublePointer ptr;
      const char *name;
   };

   // Allow both 'mod' and 'fmod' for the modulus function

   static Table t[] =
   {
      { atan2,                           "atan2"                       },
      { bit_and,                         "bit_and"                     },
      { bit_or,                          "bit_or"                      },
      { bit_shl,                         "bit_shl"                     },
      { bit_shr,                         "bit_shr"                     },
      { bit_xor,                         "bit_xor"                     },
      { fmod,                            "fmod"                        },
      { fmod,                            TwoArgFunctionDoubleNode::MOD },
      { pow,                             TwoArgFunctionDoubleNode::POW },
      { TwoArgFunctionDoubleNode::min,   "min"                         },
      { TwoArgFunctionDoubleNode::max,   "max"                         },
      { TwoArgFunctionDoubleNode::gamma, "gamma"                       },
   };

   int size = sizeof(t) / sizeof(t[0]);

   for(int i = 0; i < size; i ++)
      if(strcmp(t[i].name, name) == 0)
         return(t[i].ptr);

   return(0);
}
