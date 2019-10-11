#ifndef _STATEMENT_H_
#   define _STATEMENT_H_

#include "tf.h"

#include <iostream>

using std::ostream;

class InfiniteLoopCallback;

struct LoopControl
{
   LoopControl() : doBreak(FALSE), doContinue(FALSE) {}
   int doBreak;
   int doContinue;

};

class Statement
{
   public:
      Statement();
      virtual ~Statement();
      virtual int execute(
         InfiniteLoopCallback *callback,
         LoopControl *control
      ) const = 0;
      virtual ostream &print(ostream &out) const = 0;
};

#endif

ostream &operator<<(ostream &out, const Statement &s);
