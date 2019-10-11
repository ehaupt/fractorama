// C/C++ Headers

#include <string.h>
#include <iomanip>

using std::setprecision;

// Local Headers

#include "DoubleNodePrintArg.h"
#include "DoubleNode.h"
#include "dmemory.h"

DoubleNodePrintArg::DoubleNodePrintArg(const DoubleNode *node) :
   mNode(node)
{
}

DoubleNodePrintArg::~DoubleNodePrintArg()
{
   DDELETE(mNode);
}

void DoubleNodePrintArg::execute(ostream &out)  const
{
   double value = mNode->evaluate();
   out << setprecision(10) << value;
}

ostream & DoubleNodePrintArg::print(ostream &out) const
{
   return(mNode->print(out));
}
