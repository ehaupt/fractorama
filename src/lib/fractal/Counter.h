#ifndef _COUNTER_H_
#   define _COUNTER_H_

#include "GenericStack.h"

class Counter
{
   public:
      Counter();
      ~Counter();

   private:
      Counter(const Counter &other);
      Counter &operator=(const Counter &other);

   public:
      void beginCount();
      void increment();
      int endCount();

   private:
      GenericStack mStack;
};

#endif
