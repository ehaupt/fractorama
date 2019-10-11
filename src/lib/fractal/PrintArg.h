#ifndef _PRINT_ARG_H_
#   define _PRINT_ARG_H_

#include <iostream>

using std::ostream;

class PrintArg
{
   public:
      PrintArg();
      virtual ~PrintArg();

      virtual void execute(ostream &out) const = 0;

      virtual ostream &print(ostream &out) const = 0;

   private:
      PrintArg(const PrintArg &);
      PrintArg &operator=(const PrintArg &);
};
#endif
