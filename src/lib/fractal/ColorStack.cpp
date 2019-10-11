#include "ColorStack.h"

int ColorStack::isEmpty() const
{
   return(mStack.isEmpty());
}

void ColorStack::push(const int *ptr)
{
   mStack.push((void *)ptr);
}

const int *ColorStack::pop()
{
   return((const int *)mStack.pop());
}
