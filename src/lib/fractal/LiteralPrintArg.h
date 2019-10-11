#ifndef _LITERAL_PRINT_ARG_H_
#   define _LITERAL_PRINT_ARG_H_

#include "PrintArg.h"

class LiteralPrintArg : public PrintArg
{
   public:
      LiteralPrintArg(char *theString);
      ~LiteralPrintArg();

      void execute(ostream &out) const;

      ostream &print(ostream &out) const;

   private:
      LiteralPrintArg(const LiteralPrintArg &);
      LiteralPrintArg &operator=(const LiteralPrintArg &);

      char *mString;
};

#endif
