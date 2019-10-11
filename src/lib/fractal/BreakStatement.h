#ifndef _BREAK_STATEMENT_H_
#   define _BREAK_STATEMENT_H_

#include "Statement.h"

class BreakStatement : public Statement
{
   public:

      BreakStatement();
      ~BreakStatement();

      int execute(
         InfiniteLoopCallback *callback,
         LoopControl *control
      ) const;

      ostream &print(ostream &out) const;
};
#endif
