// Local Headers

#include "ContinueStatement.h"

ContinueStatement::ContinueStatement()
{
   // Nothing to do
}


ContinueStatement::~ContinueStatement()
{
   // Nothing to do
}

int ContinueStatement::execute(
   InfiniteLoopCallback *,
   LoopControl *control
) const
{
   control->doContinue = TRUE;

   return(TRUE);
}

ostream &ContinueStatement::print(ostream &out) const
{
   return(out << "continue");
}
