// Local Headers

#include "NullStatement.h"
#include "BooleanNode.h"

NullStatement::NullStatement()
{
   // Nothing to do
}


NullStatement::~NullStatement()
{
   // Nothing to do
}

int NullStatement::execute(
   InfiniteLoopCallback *,
   LoopControl *
) const
{
   return(TRUE);
}

ostream &NullStatement::print(ostream &out) const
{
   out << "null";
   return(out);
}
