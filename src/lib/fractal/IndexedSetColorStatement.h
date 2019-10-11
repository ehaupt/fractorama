#ifndef _INDEXED_SET_COLOR_STATEMENT_H_
#   define _INDEXED_SET_COLOR_STATEMENT_H_

class DoubleNode;
class ColorEnvironment;

#include "Statement.h"

class IndexedSetColorStatement : public Statement
{
   public:
      IndexedSetColorStatement(const DoubleNode *node, ColorEnvironment &env);
      ~IndexedSetColorStatement();

      int execute(
         InfiniteLoopCallback *callback,
         LoopControl *control
      ) const;

      ostream &print(ostream &out) const;

   private:
      const DoubleNode *mNode;
      ColorEnvironment &mEnv;
};

#endif
