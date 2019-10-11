#ifndef _COMPOUND_STATEMENT_H_
#   define _COMPOUND_STATEMENT_H_

#include "Statement.h"

class CompoundStatement : public Statement
{
   public:
      CompoundStatement();
      ~CompoundStatement();

      int execute(
         InfiniteLoopCallback *callback,
         LoopControl *control
      ) const;

      ostream &print(ostream &out) const;
      void add(const Statement *s);

   private:
      const Statement **mStatements;
      int mCount;
      
};

#endif
