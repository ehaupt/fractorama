#ifndef _RGB_SET_COLOR_STATEMENT_H_
#   define _RGB_SET_COLOR_STATEMENT_H_

class DoubleNode;
class ColorEnvironment;

#include "Statement.h"

class RGBSetColorStatement : public Statement
{
   public:
      RGBSetColorStatement(
         const DoubleNode *redNode,
         const DoubleNode *greenNode,
         const DoubleNode *blueNode,
         ColorEnvironment &env
      );

      ~RGBSetColorStatement();

      int execute(
         InfiniteLoopCallback *callback,
         LoopControl *control
      ) const;

      ostream &print(ostream &out) const;

   private:
      const DoubleNode *mRed;
      const DoubleNode *mGreen;
      const DoubleNode *mBlue;
      ColorEnvironment &mEnv;
};

#endif
