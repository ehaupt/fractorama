// C/C++ Headers

#include <string.h>
#include <math.h>


// Local Headers

#include "OneArgFunctionDoubleNode.h"
#include "AttributeDoubleNode.h"
#include "dmemory.h"

OneArgFunctionDoubleNode::OneArgFunctionDoubleNode(
   char *methodName,
   OneArgFunctionDoublePointer ptr,
   const DoubleNode *nodePtr
)  :
   mPtr(ptr),
   mNodePtr(nodePtr)
{
   DNEW(mName, char[strlen(methodName) + 1]);
   strcpy(mName, methodName);
}

OneArgFunctionDoubleNode::~OneArgFunctionDoubleNode()
{
   DADELETE(mName);
   DDELETE(mNodePtr);
}

OneArgFunctionDoublePointer OneArgFunctionDoubleNode::lookup(char *name)
{
   struct Table
   {
      OneArgFunctionDoublePointer ptr;
      char *name;
   };

   // Allow both 'fabs' and 'abs' for absolute value

   static Table t[] =
   {
      { acsc,      "acsc"      },
      { acsch,     "acsch"     },
      { acos,      "acos"      },
      { acosh,     "acosh"     },
      { acot,      "acot"      },
      { acoth,     "acoth"     },
      { asec,      "asec"      },
      { asech,     "asech"     },
      { asin,      "asin"      },
      { asinh,     "asinh"     },
      { atan,      "atan"      },
      { atanh,     "atanh"     },
      { bernoulli, "bernoulli" },
      { bit_not,   "bit_not"   },
      { ceil,      "ceil"      },
      { cos,       "cos"       },
      { cosh,      "cosh"      },
      { cot,       "cot"       },
      { coth,      "coth"      },
      { csc,       "csc"       },
      { csch,      "csch"      },
      { deg2rad,   "deg2rad"   },
      { euler,     "euler",    },
      { exp,       "exp"       },
      { fabs,      "abs"       },
      { fabs,      "fabs"      },
      { factorial, "fact"      },
      { floor,     "floor"     },
      { log,       "log"       },
      { log10,     "log10"     },
      { rad2deg,   "rad2deg"   },
      { sec,       "sec"       },
      { sech,      "sech"      },
      { sin,       "sin"       },
      { sinh,      "sinh"      },
      { sqrt,      "sqrt"      },
      { tan,       "tan"       },
      { tanh,      "tanh"      },
   };

   int size = sizeof(t) / sizeof(t[0]);

   for(int i = 0; i < size; i ++)
      if(strcmp(t[i].name, name) == 0)
         return(t[i].ptr);

   return(0);
}

double OneArgFunctionDoubleNode::evaluate() const
{
   return(mPtr(mNodePtr->evaluate()));
}

ostream &OneArgFunctionDoubleNode::print(ostream &out) const
{
   out << mName << "(";
   mNodePtr->print(out);
   out << ")";

   return(out);
}

double OneArgFunctionDoubleNode::asec(double value)
{
   return(acos(1.0 / value));
}

double OneArgFunctionDoubleNode::acsc(double value)
{
   return(asin(1.0 / value));
}

double OneArgFunctionDoubleNode::acot(double value)
{
   return(atan(1.0 / value));
}

double OneArgFunctionDoubleNode::asinh(double value)
{
   return(log(value + sqrt(value * value + 1.0)));
}

double OneArgFunctionDoubleNode::acosh(double value)
{
   return(log(value + sqrt(value * value - 1.0)));
}

double OneArgFunctionDoubleNode::atanh(double value)
{
   return(log((value + 1.0) / (value - 1.0)) / 2.0);
}

double OneArgFunctionDoubleNode::asech(double value)
{
   return(acosh(1.0 / value));
}

double OneArgFunctionDoubleNode::acsch(double value)
{
   return(asinh(1.0 / value));
}

double OneArgFunctionDoubleNode::acoth(double value)
{
   return(atanh(1.0 / value));
}

double OneArgFunctionDoubleNode::cot(double value)
{
   return(cos(value) / sin(value));
}

double OneArgFunctionDoubleNode::sec(double value)
{
   return(1.0 / cos(value));
}

double OneArgFunctionDoubleNode::csc(double value)
{
   return(1.0 / sin(value));
}

double OneArgFunctionDoubleNode::coth(double value)
{
   return(cosh(value) / sinh(value));
}

double OneArgFunctionDoubleNode::sech(double value)
{
   return(1.0 / cosh(value));
}

double OneArgFunctionDoubleNode::csch(double value)
{
   return(1.0 / sinh(value));
}

double OneArgFunctionDoubleNode::factorial(double x)
{
   double result = 0.0;

   if(x >= 0)
   {
      if((int)x == x)
      {
         result = 1.0;

         while(x > 1)
         {
            result *= x;
            x      -= 1;
         }
      }
      else
      {
         static double coefficients[6] =
         {
            76.18009172947146,     -86.50532032941677,
            24.01409824083091,     -1.231739572450155,
            0.1208650973866179e-2, -0.5395239384953e-5
         };

         double value1 = x + 1;
         double value2 = value1;
         double value3 = value1 + 5.5 - (value1 + 0.5) * log(value1 + 5.5);
         double value4 = 1.000000000190015;

         for(int i = 0; i < 6; i ++)
            value4 += (coefficients[i] / ++value2);

         result = exp(log(2.5066282746310005 * value4 / value1) - value3);
      }
   }

   return(result);
}

double OneArgFunctionDoubleNode::rad2deg(double radians)
{
   return(radians * AttributeDoubleNode::DEGREES_PER_RADIAN);
}

double OneArgFunctionDoubleNode::deg2rad(double degrees)
{
   return(degrees / AttributeDoubleNode::DEGREES_PER_RADIAN);
}

double OneArgFunctionDoubleNode::bernoulli(double value)
{
   static double numbers[] =
   {
      1.0,
      -0.5,
      .1666666667,
      0.0,
      -.0333333333,
      0.0,
      .0238095238,
      0.0,
      -.0333333333,
      0.0,
      .0757575758,
      0.0,
      -.2531135531,
      0.0,
      1.1666666667,
      0.0,
      -7.0921568627,
      0.0,
      54.9711779449,
      0.0,
      -529.1242424242,
      0.0,
      6192.1231884058,
      0.0,
      -86580.2531135531,
      0.0,
      1425517.1666666667,
      0.0,
      -27298231.067816092,
      0.0,
      601580873.9006423684,
      0.0,
      -15116315767.0921568627,
      0.0,
      429614643061.1666666667,
      0.0,
      -13711655205088.3327721591,
      0.0,
      488332318973593.1666666667,
      0.0,
      -19296579341940068.1486326681
   };

   static int size = sizeof(numbers) / sizeof(numbers[0]);

   if(value < 0.0)
      return(0.0);

   int iValue = (int)value;

   if(iValue % 2 == 1)
      return(0.0);

   return(numbers[iValue >= size ? size - 1 : iValue]);
}

double OneArgFunctionDoubleNode::euler(double value)
{
   static double numbers[] =
   {
      1.0,
      0.0,
      -1.0,
      0.0,
      5.0,
      0.0,
      -61.0,
      0.0,
      1385.0,
      0.0,
      -50521.0,
      0.0,
      2702765.0,
      0.0,
      -199360981.0,
      0.0,
      19391512145.0,
      0.0,
      -2404879675441.0,
      0.0,
      370371188237525.0
   };

   static int size = sizeof(numbers) / sizeof(numbers[0]);

   if(value < 0.0)
      return(0.0);

   int iValue = (int)value;

   if(iValue % 2 == 1)
      return(0.0);

   return(numbers[iValue >= size ? size - 1 : iValue]);
}

double OneArgFunctionDoubleNode::bit_not(double value)
{
   return(~RND(value));
}
