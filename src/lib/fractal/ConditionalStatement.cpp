// Local Headers

#include "ConditionalStatement.h"
#include "BooleanNode.h"
#include "dmemory.h"

ConditionalStatement::ConditionalStatement(
   const Statement   **statements,
   const BooleanNode **conditions,
   int count,
   const Statement *elseStatement
)  :
   mStatements(statements),
   mConditions(conditions),
   mCount(count),
   mElse(elseStatement)
{
}

ConditionalStatement::~ConditionalStatement()
{
   for(int i = 0; i < mCount; i ++)
   {
      DDELETE(mStatements[i]);
      DDELETE(mConditions[i]);
   }

   DADELETE(mStatements);
   DADELETE(mConditions);

   if(mElse)
      DDELETE(mElse);
}

int ConditionalStatement::execute(
   InfiniteLoopCallback *callback,
   LoopControl *control
) const
{
   int status = TRUE;
   int i      = 0;

   for(i = 0; i < mCount; i ++)
   {
      const BooleanNode *condition = mConditions[i];

      if(condition->evaluate())
      {
         const Statement *statement = mStatements[i];

         status = statement->execute(callback, control);
         break;
      }
   }

   if(i == mCount)
   {
      if(mElse)
      {
         status = mElse->execute(callback, control);
      }
   }

   return(status);
}

ostream &ConditionalStatement::print(ostream &out) const
{
   for(int i = 0; i < mCount; i ++)
   {
      Statement *statement   = (Statement *)mStatements[i];
      BooleanNode *condition = (BooleanNode *)mConditions[i];

      out << (i == 0 ? "if" : "elseif") << "(";

      condition->print(out);

      out << ") {\n";

      statement->print(out);

      out << "}";
   }

   if(mElse)
   {
      out << "else {";
      mElse->print(out);
      out << "}";
   }

   return(out);
}
