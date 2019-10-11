// Local Headers

#include "BreakStatement.h"

BreakStatement::BreakStatement()
{
   // Nothing to do
}


BreakStatement::~BreakStatement()
{
   // Nothing to do
}

int BreakStatement::execute(
   InfiniteLoopCallback *,
   LoopControl *control
) const
{
   control->doBreak = TRUE;

   return(TRUE);
}

ostream &BreakStatement::print(ostream &out) const
{
   return(out << "break");
}
