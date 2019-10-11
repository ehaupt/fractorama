#ifndef _DOUBLE_NODE_PRINT_ARG_H_
#   define _DOUBLE_NODE_PRINT_ARG_H_

#include "PrintArg.h"

class DoubleNode;

class DoubleNodePrintArg : public PrintArg
{
   public:
      DoubleNodePrintArg(const DoubleNode *node);
      ~DoubleNodePrintArg();

      void execute(ostream &out)  const;

      ostream &print(ostream &out) const;

   private:
      DoubleNodePrintArg(const DoubleNodePrintArg &);
      DoubleNodePrintArg &operator=(const DoubleNodePrintArg &);

      const DoubleNode *mNode;
};

#endif
