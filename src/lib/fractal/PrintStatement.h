#ifndef _PRINT_STATEMENT_H_
#   define _PRINT_STATEMENT_H_

#include "Statement.h"

class PrintArg;

class PrintStatement : public Statement
{
   public:
      PrintStatement(int addNewLine = 0);

      ~PrintStatement();

      int execute(
         InfiniteLoopCallback *callback,
         LoopControl *control
      )  const;

      ostream &print(ostream &out) const;

      void addPrintArg(const PrintArg *arg);
      void setDestination(char *fileName);

   private:
      const PrintArg **mArgs;
      int   mArgCount;
      int   mWriteToStdout;
      int   mAddNewLine;
      char *mFileName;
};
#endif
