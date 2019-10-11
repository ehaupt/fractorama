// Local Headers

#include "ForStatement.h"
#include "BooleanNode.h"
#include "InfiniteLoopCallback.h"
#include "dmemory.h"

ForStatement::ForStatement(
   const Statement   *initializeStatement,
   const BooleanNode *condition,
   const Statement   *incrementStatement,
   const Statement   *bodyStatement
)  :
   mInitializeStatement(initializeStatement),
   mCondition(condition),
   mIncrementStatement(incrementStatement),
   mBodyStatement(bodyStatement)
{
}

ForStatement::~ForStatement()
{
   DDELETE(mCondition);
   DDELETE(mInitializeStatement);
   DDELETE(mIncrementStatement);
   DDELETE(mBodyStatement);
}

int ForStatement::execute(
   InfiniteLoopCallback *callback,
   LoopControl *control
)  const
{
   int i      = 0;
   int status = TRUE;

   status = mInitializeStatement->execute(callback, control);

   if(!status)
      return(status);

   if(control->doBreak || control->doContinue)
      return(TRUE);

   while(mCondition->evaluate())
   {
      LoopControl forLoopControl;

      if((i + 1) % InfiniteLoopCallback::NITERATIONS == 0)
      {
         if(callback->abortProcessing())
         {
            status = FALSE;
            break;
         }
      }

      if(!mBodyStatement->execute(callback, &forLoopControl))
      {
         status = FALSE;
         break;
      }

      if(forLoopControl.doBreak)
         break;

      // No need to handle 'forLoopControl.doContinue'
      // as it drops us out of executing the sequence
      // of statements in 'mBodyStatement' already

      if(!mIncrementStatement->execute(callback, control))
      {
         status = FALSE;
         break;
      }

      if(control->doBreak || control->doContinue)
         break;

      i++;
   }

   return(status);
}

ostream &ForStatement::print(ostream &out) const
{
   out << "for(";
   mInitializeStatement->print(out) << ";";
   mCondition->print(out) << ";";
   mIncrementStatement->print(out) << ")\n";

   out << "{\n";
   mBodyStatement->print(out);
   out << "}";
   return(out);
}
