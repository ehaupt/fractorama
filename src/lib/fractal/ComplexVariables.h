#ifndef _COMPLEX_VARIABLES_H_
#   define _COMPLEX_VARIABLES_H_

#include "dcomplex.h"
#include <iostream>

using std::ostream;

struct ComplexEntry;

class ComplexVariables
{
   public:
      ComplexVariables();
      ~ComplexVariables();
      dcomplex *assign(const char *name);
      dcomplex *lookup(const char *name) const;
      void initialize();
      ostream &print(ostream &out) const;

      static const dcomplex ZERO;

   private:
      ComplexVariables(const ComplexVariables &other);
      ComplexVariables &operator=(const ComplexVariables &other);

      int mCount;
      ComplexEntry **mEntries;
};

ostream &operator<<(ostream &out, const ComplexVariables &cv);

#endif
