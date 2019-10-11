#ifndef _NULL_STATEMENT_H_
#   define _NULL_STATEMENT_H_

#include "Statement.h"

class BooleanNode;

class NullStatement : public Statement
{
   public:
      NullStatement();
      ~NullStatement();

      int execute(
         InfiniteLoopCallback *callback,
         LoopControl *control
      ) const;

      ostream &print(ostream &out) const;
};
#endif
