#ifndef _CONTINUE_STATEMENT_H_
#   define _CONTINUE_STATEMENT_H_

#include "Statement.h"

class ContinueStatement : public Statement
{
   public:

      ContinueStatement();
      ~ContinueStatement();

      int execute(
         InfiniteLoopCallback *callback,
         LoopControl *control
      ) const;

      ostream &print(ostream &out) const;
};
#endif
