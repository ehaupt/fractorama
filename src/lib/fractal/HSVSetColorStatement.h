#ifndef _HSV_SET_COLOR_STATEMENT_H_
#   define _HSV_SET_COLOR_STATEMENT_H_

class DoubleNode;
class ColorEnvironment;

#include "Statement.h"

class HSVSetColorStatement : public Statement
{
   public:
      HSVSetColorStatement(
         const DoubleNode *hNode,
         const DoubleNode *sNode,
         const DoubleNode *vNode,
         ColorEnvironment &env
      );

      ~HSVSetColorStatement();

      int execute(
         InfiniteLoopCallback *callback,
         LoopControl *control
      ) const;

      static void hsv2rgb(
         double h, double s, double v, double *r, double *g, double *b
      );

      ostream &print(ostream &out) const;

   private:
      const DoubleNode *mH;
      const DoubleNode *mS;
      const DoubleNode *mV;
      ColorEnvironment &mEnv;
};

#endif
