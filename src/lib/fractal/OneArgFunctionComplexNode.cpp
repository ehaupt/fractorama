// C/C++ Headers

#include <string.h>

// Local Headers

#include "OneArgFunctionComplexNode.h"
#include "dmemory.h"

const dcomplex OneArgFunctionComplexNode::I        = dcomplex(0, 1);
const dcomplex OneArgFunctionComplexNode::MINUS_I  = dcomplex(0, -1);
const dcomplex OneArgFunctionComplexNode::I_OVER_2 = dcomplex(0, .5);

OneArgFunctionComplexNode::OneArgFunctionComplexNode(
   char *methodName,
   OneArgFunctionComplexPointer ptr,
   const ComplexNode *nodePtr
)  :
   mPtr(ptr),
   mNodePtr(nodePtr)
{
   DNEW(mName, char[strlen(methodName) + 1]);
   strcpy(mName, methodName);
}

OneArgFunctionComplexNode::~OneArgFunctionComplexNode()
{
   DADELETE(mName);
   DDELETE(mNodePtr);
}

OneArgFunctionComplexPointer OneArgFunctionComplexNode::lookup(char *name)
{
   struct Table
   {
      OneArgFunctionComplexPointer ptr;
      char *name;
   };

   static Table t[] =
   {
      { acos,      "acos"  },
      { acosh,     "acosh" },
      { acot,      "acot"  },
      { acoth,     "acoth" },
      { acsc,      "acsc"  },
      { acsch,     "acsch" },
      { asec,      "asec"  },
      { asech,     "asech" },
      { asin,      "asin"  },
      { asinh,     "asinh" },
      { atan,      "atan"  },
      { atanh,     "atanh" },
      { STD(conj), "conj"  },
      { STD(cos),  "cos"   },
      { STD(cosh), "cosh"  },
      { cot,       "cot"   },
      { coth,      "coth"  },
      { csc,       "csc"   },
      { csch,      "csch"  },
      { STD(exp),  "exp"   },
      { STD(log),  "log"   },
      { sec,       "sec"   },
      { sech,      "sech"  },
      { STD(sin),  "sin"   },
      { STD(sinh), "sinh"  },
      { STD(sqrt), "sqrt"  },
      { tan,       "tan"   },
      { tanh,      "tanh"  },
   };

   int size = sizeof(t) / sizeof(t[0]);

   for(int i = 0; i < size; i ++)
      if(strcmp(t[i].name, name) == 0)
         return(t[i].ptr);

   return(0);
}

dcomplex OneArgFunctionComplexNode::evaluate() const
{
   return(
      mPtr(
         mNodePtr->evaluate()
      )
   );
}

ostream &OneArgFunctionComplexNode::print(ostream &out) const
{
   out << mName << "(";
   mNodePtr->print(out);
   out << ")";   

   return(out);
}

dcomplex OneArgFunctionComplexNode::asin(const dcomplex &value)
{
   return(
      MINUS_I * STD(log)(I * value + STD(sqrt)(1.0 - value * value))
   );
}

dcomplex OneArgFunctionComplexNode::acos(const dcomplex &value)
{
   return(
      MINUS_I * STD(log)(value + I * STD(sqrt)(1.0 - value * value))
   );
}

dcomplex OneArgFunctionComplexNode::atan(const dcomplex &value)
{
   return(
      I_OVER_2 * STD(log)((I + value) / (I - value))
   );
}

dcomplex OneArgFunctionComplexNode::asec(const dcomplex &value)
{
   return(acos(1.0 / value));
}

dcomplex OneArgFunctionComplexNode::acsc(const dcomplex &value)
{
   return(asin(1.0 / value));
}

dcomplex OneArgFunctionComplexNode::acot(const dcomplex &value)
{
   return(atan(1.0 / value));
}

dcomplex OneArgFunctionComplexNode::asinh(const dcomplex &value)
{
   return(STD(log)(value + STD(sqrt)(value * value + 1.0)));
}

dcomplex OneArgFunctionComplexNode::acosh(const dcomplex &value)
{
   return(STD(log)(value + STD(sqrt)(value * value - 1.0)));
}

dcomplex OneArgFunctionComplexNode::atanh(const dcomplex &value)
{
   return(STD(log)((1.0 + value) / (1.0 - value)) / 2.0);
}

dcomplex OneArgFunctionComplexNode::asech(const dcomplex &value)
{
   return(acosh(1.0 / value));
}

dcomplex OneArgFunctionComplexNode::acsch(const dcomplex &value)
{
   return(asinh(1.0 / value));
}

dcomplex OneArgFunctionComplexNode::acoth(const dcomplex &value)
{
   return(atanh(1.0 / value));
}

dcomplex OneArgFunctionComplexNode::tan(const dcomplex &value)
{
   return(STD(sin)(value) / STD(cos)(value));
}

dcomplex OneArgFunctionComplexNode::cot(const dcomplex &value)
{
   return(STD(cos)(value) / STD(sin)(value));
}

dcomplex OneArgFunctionComplexNode::sec(const dcomplex &value)
{
   return(1.0 / STD(cos)(value));
}

dcomplex OneArgFunctionComplexNode::csc(const dcomplex &value)
{
   return(1.0 / STD(sin)(value));
}

dcomplex OneArgFunctionComplexNode::tanh(const dcomplex &value)
{
   return(STD(sinh(value)) / STD(cosh(value)));
}

dcomplex OneArgFunctionComplexNode::sech(const dcomplex &value)
{
   return(1.0 / STD(cosh)(value));
}

dcomplex OneArgFunctionComplexNode::csch(const dcomplex &value)
{
   return(1.0 / STD(sinh)(value));
}

dcomplex OneArgFunctionComplexNode::coth(const dcomplex &value)
{
   return(STD(cosh(value)) / STD(sinh(value)));
}
