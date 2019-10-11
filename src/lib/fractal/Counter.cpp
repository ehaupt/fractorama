#include "Counter.h"
#include "dmemory.h"

Counter::Counter() {}

Counter::~Counter() {}

void Counter::beginCount()
{
   int *ptr = 0;
   DNEW(ptr, int);

   *ptr = 0;

   mStack.push(ptr);
}

void Counter::increment()
{
   int *ptr  = (int *)mStack.pop();
   (*ptr)++;

   mStack.push(ptr);
}

int Counter::endCount()
{
   int *ptr  = (int *)mStack.pop();
   int value = *ptr;

   DDELETE(ptr);

   return(value);
}
