#ifndef _DOUBLE_VARIABLES_H_
#   define _DOUBLE_VARIABLES_H_

#include <iostream>

using std::ostream;

struct DoubleEntry;

class DoubleVariables
{
   public:
      DoubleVariables();
      ~DoubleVariables();
      double *assign(const char *name);
      double *lookup(const char *name) const;
      void initialize();
      ostream &print(ostream &out) const;

      static const double ZERO;

   private:
      DoubleVariables(const DoubleVariables &other);
      DoubleVariables &operator=(const DoubleVariables &other);

      int mCount;
      DoubleEntry **mEntries;
};

ostream &operator<<(ostream &out, const DoubleVariables &dv);

#endif
