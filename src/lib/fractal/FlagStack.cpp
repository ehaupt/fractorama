#include "FlagStack.h"
#include "dmemory.h"

int FlagStack::isEmpty() const
{
   return(mStack.isEmpty());
}

void FlagStack::push(int value)
{
   int *ptr = 0;
   DNEW(ptr, int);

   *ptr = value;

   mStack.push((void *)ptr);
}

const int FlagStack::top()
{
   int *ptr  = (int *)mStack.top();
   return(*ptr);
}

const int FlagStack::pop()
{
   int *ptr  = (int *)mStack.pop();
   int value = *ptr;

   DDELETE(ptr);
   return(value);
}
