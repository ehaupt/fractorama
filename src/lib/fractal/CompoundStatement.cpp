// Local Headers

#include "CompoundStatement.h"
#include "dmemory.h"

CompoundStatement::CompoundStatement() :
   mStatements(0),
   mCount(0)
{
}

CompoundStatement::~CompoundStatement()
{
   for(int i = 0; i < mCount; i ++)
      DDELETE(mStatements[i]);

   DADELETE(mStatements);
}

int CompoundStatement::execute(
   InfiniteLoopCallback *callback,
   LoopControl *control
) const
{
   for(int i = 0; i < mCount; i ++)
   {
      if(!mStatements[i]->execute(callback, control))
         return(FALSE);

      if(control->doBreak || control->doContinue)
         break;
   }

   return(TRUE);
}

ostream &CompoundStatement::print(ostream &out) const
{
   for(int i = 0; i < mCount; i ++)
   {
      mStatements[i]->print(out);
      out << "\n";
   }

   return(out);
}

void CompoundStatement::add(const Statement *s)
{
   const Statement **array = 0;
   DNEW(array, const Statement *[mCount + 1]);

   for(int i = 0; i < mCount; i ++)
      array[i] = mStatements[i];

   array[mCount++] = s;

   if(mStatements)
      DADELETE(mStatements);

   mStatements = array;
}
