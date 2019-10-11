// C/C++ Headers

#include <string.h>
#include <iostream>
#include <fstream>

using std::ostream;
using std::ofstream;
using std::ios;
using std::endl;
using std::cout;

// Local Headers

#include "PrintStatement.h"
#include "PrintArg.h"
#include "dmemory.h"

PrintStatement::PrintStatement(int addNewLine) :
   mArgs(0),
   mArgCount(0),
   mAddNewLine(addNewLine),
   mFileName(0)
{
}

PrintStatement::~PrintStatement()
{
   DADELETE(mFileName);

   for(int i = 0; i < mArgCount; i ++)
      DDELETE(mArgs[i]);

   DADELETE(mArgs);
}

int PrintStatement::execute(InfiniteLoopCallback *, LoopControl *)  const
{
   // Ok, where are we writing to?

   int writeToStdout = TRUE;

   if(mFileName != NULL)
   {
      ofstream out(mFileName, ios::out|ios::app);

      if(out)
      {
         for(int i = 0; i < mArgCount; i ++)
            mArgs[i]->execute(out);

         if(mAddNewLine)
            out << endl;

         writeToStdout = FALSE;
      }
   }

   if(writeToStdout)
   {
      for(int i = 0; i < mArgCount; i ++)
         mArgs[i]->execute(cout);

      if(mAddNewLine)
         cout << endl;
   }

   return(TRUE);
}

ostream &PrintStatement::print(ostream &out) const
{
   out << "print(";

   if(mFileName == NULL)
      out << "stdout";
   else
      out << "\"" << mFileName << "\"";

   out << ", ";

   for(int i = 0; i < mArgCount; i ++)
   {
      if(i > 0)
         out << " . ";

      mArgs[i]->print(out);
   }

   return(out << ")");
}

void PrintStatement::addPrintArg(const PrintArg *arg)
{
   const PrintArg **newArgs = 0;
   DNEW(newArgs, const PrintArg *[mArgCount + 1]);

   for(int i = 0; i < mArgCount; i ++)
      newArgs[i] = mArgs[i];

   newArgs[mArgCount] = arg;

   DADELETE(mArgs);
   mArgCount++;
   mArgs = newArgs;
}

void PrintStatement::setDestination(char *fileName)
{
   DADELETE(mFileName);
   int size  = strlen(fileName) + 1;
   DNEW(mFileName, char[size]);
   strcpy(mFileName, fileName);
}
