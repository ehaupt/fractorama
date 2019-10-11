// C/C++ Headers

#include <string.h>
#include <iomanip>

using std::setprecision;

// Local Headers

#include "ComplexNodePrintArg.h"
#include "ComplexNode.h"
#include "dmemory.h"

ComplexNodePrintArg::ComplexNodePrintArg(const ComplexNode *node) :
   mNode(node)
{
}

ComplexNodePrintArg::~ComplexNodePrintArg()
{
   DDELETE(mNode);
}

void ComplexNodePrintArg::execute(ostream &out)  const
{
   dcomplex value = mNode->evaluate();

   out << setprecision(10) <<
      "[" << __REAL(value) << ", " << __IMAG(value) << "]";
}

ostream & ComplexNodePrintArg::print(ostream &out) const
{
   return(mNode->print(out));
}
