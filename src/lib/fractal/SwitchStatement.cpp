// Local Headers

#include "SwitchStatement.h"
#include "DoubleNode.h"
#include "CompoundStatement.h"
#include "dmemory.h"

/********************************************************************
 * Local Class: CaseEntry
 ********************************************************************/

class CaseEntry
{
   public:
      CaseEntry();
      ~CaseEntry();
      void addNode(const DoubleNode *node);
      void addStatements(const CompoundStatement *statement);
      void setBreak();

      int matches(double value);

      void execute(
         InfiniteLoopCallback *callback,
         LoopControl *control
      );

      int hasBreak();
      int isDefault() const;

      ostream & print(ostream &out) const;

   private:
      const DoubleNode **mEntries;
      int mCount;
      int mHasBreak;
      CompoundStatement *mStatement;
};

CaseEntry::CaseEntry() :
   mEntries(0),
   mCount(0),
   mHasBreak(0),
   mStatement(0)
{
}

CaseEntry::~CaseEntry()
{
   for(int i = 0; i < mCount; i ++)
      DDELETE(mEntries[i]);

   DADELETE(mEntries);
   DDELETE(mStatement);
}

void CaseEntry::addNode(const DoubleNode *node)
{
   const DoubleNode **array = 0;
   DNEW(array, const DoubleNode *[mCount + 1]);

   for(int i = 0; i < mCount; i ++)
      array[i] = mEntries[i];

   array[mCount++] = node;

   if(mEntries)
      DADELETE( mEntries);

   mEntries = array;
}

void CaseEntry::addStatements(const CompoundStatement *statement)
{
   mStatement = (CompoundStatement *)statement;
}

void CaseEntry::setBreak()
{
   mHasBreak = TRUE;
}

int CaseEntry::matches(double value)
{
   if(isDefault())
      return(TRUE);

   for(int i = 0; i < mCount; i ++)
   {
      double theValue = mEntries[i]->evaluate();

      if(theValue == value)
         return(TRUE);
   }

   return(FALSE);
}

void CaseEntry::execute(
   InfiniteLoopCallback *callback,
   LoopControl *control
)
{
   mStatement->execute(callback, control);
}

int CaseEntry::hasBreak()
{
   return(mHasBreak);
}

int CaseEntry::isDefault() const
{
   return(mCount == 0);
}

ostream & CaseEntry::print(ostream &out) const
{
   if(isDefault())
   {
      out << "default:\n";
   }
   else
   {
      for(int i = 0; i < mCount; i ++)
      {
         out << "case ";
         mEntries[i]->print(out);
         out << ":\n";
      }
   }

   out << "{\n";

   mStatement->print(out);

   out << "}\n";

   return(out);
}

/*****************************************************************************
 * class: SwitchStatement
 *****************************************************************************/

SwitchStatement::SwitchStatement(const DoubleNode *node) :
   mNode(node),
   mEntries(0),
   mCount(0)
{
}

SwitchStatement::~SwitchStatement()
{
   DDELETE(mNode);

   for(int i = 0; i < mCount; i ++)
      DDELETE(mEntries[i]);

   DADELETE(mEntries);
}

void SwitchStatement::caseBegin()
{
   CaseEntry **array = 0;
   DNEW(array, CaseEntry *[mCount + 1]);

   for(int i = 0; i < mCount; i ++)
      array[i] = mEntries[i];

   DNEW(array[mCount], CaseEntry());
   mCount++;

   if(mEntries)
      DADELETE(mEntries);

   mEntries = array;
}

void SwitchStatement::caseAddNode(const DoubleNode *node)
{
   mEntries[mCount - 1]->addNode(node);
}

void SwitchStatement::caseAddStatements(const CompoundStatement *statement)
{
   mEntries[mCount - 1]->addStatements(statement);
}

void SwitchStatement::caseSetBreak()
{
   mEntries[mCount - 1]->setBreak();
}

int SwitchStatement::execute(
   InfiniteLoopCallback *callback,
   LoopControl *control
)  const
{
   int matchFound = 0;
   double value   = mNode->evaluate();

   for(int i = 0; i < mCount; i ++)
   {
      if(matchFound || mEntries[i]->matches(value))
      {
         mEntries[i]->execute(callback, control);

         if(mEntries[i]->hasBreak())
            break;

         matchFound = 1;
      }
   }

   return(TRUE);
}

ostream &SwitchStatement::print(ostream &out) const
{
   out << "switch(";
   mNode->print(out) << ")\n";
   out << "{\n";

   for(int i = 0; i < mCount; i ++)
      mEntries[i]->print(out);

   out << "}\n";
   return(out);
}
