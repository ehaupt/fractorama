#ifndef _COMPLEX_NODE_PRINT_ARG_H_
#   define _COMPLEX_NODE_PRINT_ARG_H_

#include "PrintArg.h"

class ComplexNode;

class ComplexNodePrintArg : public PrintArg
{
   public:
      ComplexNodePrintArg(const ComplexNode *node);
      ~ComplexNodePrintArg();

      void execute(ostream &out) const;

      ostream &print(ostream &out) const;

   private:
      ComplexNodePrintArg(const ComplexNodePrintArg &);
      ComplexNodePrintArg &operator=(const ComplexNodePrintArg &);

      const ComplexNode *mNode;
};

#endif
