// C/C++ Headers

#include <math.h>
#include <string.h>

// Local Headers

#include "AttributeDoubleNode.h"
#include "ComplexNode.h"
#include "dmemory.h"

const double AttributeDoubleNode::PI                 = 3.14159265358979323846;
const double AttributeDoubleNode::PI_OVER_TWO        = PI / 2.0;
const double AttributeDoubleNode::THREE_PI_OVER_TWO  = 3.0 * PI / 2.0;
const double AttributeDoubleNode::TWO_PI             = 2.0 * PI;
const double AttributeDoubleNode::DEGREES_PER_RADIAN = 180.0 / PI;

AttributeDoubleNode *AttributeDoubleNode::create(
   char *methodName,
   const ComplexNode *node
)
{
   AttributeFunctionPointer afp = AttributeDoubleNode::lookup(methodName);
   AttributeDoubleNode *newNode = 0;

   if(afp)
   {
      DNEW(newNode, AttributeDoubleNode(methodName, afp, node));
   }
   
   return(newNode);
}

AttributeDoubleNode::~AttributeDoubleNode()
{
   DADELETE(mMethodName);
   DDELETE(mNode);
}

double AttributeDoubleNode::evaluate() const
{
   return(mPtr(mNode->evaluate()));
}

ostream &AttributeDoubleNode::print(ostream &out) const
{
   out << mMethodName << "(";
   mNode->print(out);
   out << ")";

   return(out);
}

/*****************************************************************************
 * Private Methods
 *****************************************************************************/

AttributeDoubleNode::AttributeDoubleNode(
   char *methodName,
   AttributeFunctionPointer ptr,
   const ComplexNode *node
)  :
   mMethodName(0),
   mPtr(ptr),
   mNode(node)
{
   DNEW(mMethodName, char[strlen(methodName) + 1]);
   strcpy(mMethodName, methodName);
}

AttributeFunctionPointer AttributeDoubleNode::lookup(char *name)
{
   struct Table
   {
      AttributeFunctionPointer ptr;
      char *name;
      char *shortName;
   };

   /***********************************************************************
    * The strings listed here *must* be kept in sync with the token
    * names listed in fractal.lex
    ***********************************************************************/

   static Table t[] =
   {
      { AttributeDoubleNode::degrees,        "degrees",        "deg"     },
      { AttributeDoubleNode::old_degrees,    "old_degrees",    "old_deg" },
      { AttributeDoubleNode::radians,        "radians",        "rad"     },
      { AttributeDoubleNode::old_radians,    "old_radians",    "old_rad" },
      { AttributeDoubleNode::real,           "real",           "real"    },
      { AttributeDoubleNode::imaginary,      "imaginary",      "imag"    },
      { AttributeDoubleNode::sum_of_squares, "sum_of_squares", "ssq"     },
      { AttributeDoubleNode::magnitude,      "magnitude",      "mag"     },
   };

   int size = sizeof(t) / sizeof(t[0]);

   for(int i = 0; i < size; i ++)
   {
      if(strcmp(t[i].name,      name) == 0 ||
         strcmp(t[i].shortName, name) == 0)
      {
         return(t[i].ptr);
      }
   }

   return(0);
}


double AttributeDoubleNode::degrees(const dcomplex value)
{
   return(AttributeDoubleNode::radians(value) * DEGREES_PER_RADIAN);
}

double AttributeDoubleNode::old_degrees(const dcomplex value)
{
   return(AttributeDoubleNode::old_radians(value) * DEGREES_PER_RADIAN);
}

double AttributeDoubleNode::radians(const dcomplex value)
{
   double _real = __REAL(value);
   double _imag = __IMAG(value);

   if(_real == 0.0 && _imag == 0.0)
      return(0.0);

   // The result from atan2 will be in [-pi, pi] inclusive, we want it
   // to be in [0, 2 * pi)

   double result = atan2(_imag, _real);

   if(result < 0)
      result = TWO_PI + result;

   return(result);
}

double AttributeDoubleNode::old_radians(const dcomplex value)
{
   // This function is a backward compatibility aid - it does the radians
   // calculation the (incorrect) way we did it up to version 1.5.1
   // which actually returned the radians of 'value' offset by PI radians

   double _real = __REAL(value);
   double _imag = __IMAG(value);

   if(_real == 0.0 && _imag == 0.0)
      return(0.0);

   // Move result from atan2 from [-pi, pi] to [0, 2*pi]

   double result = atan2(_imag, _real) + PI;

   // Ensure 0.0 <= result < 2*pi

   return(result == TWO_PI ? 0.0 : result);
}

double AttributeDoubleNode::real(const dcomplex value)
{
   return(__REAL(value));
}

double AttributeDoubleNode::imaginary(const dcomplex value)
{
   return(__IMAG(value));
}

double AttributeDoubleNode::sum_of_squares(const dcomplex value)
{
   double _real = __REAL(value);
   double _imag = __IMAG(value);

   return(_real * _real + _imag * _imag);
}

double AttributeDoubleNode::magnitude(const dcomplex value)
{
   return(sqrt(AttributeDoubleNode::sum_of_squares(value)));
}
