#include "ColorNodeStack.h"

int ColorNodeStack::isEmpty() const
{
   return(mStack.isEmpty());
}

void ColorNodeStack::push(const ColorNode *ptr)
{
   mStack.push((void *)ptr);
}

const ColorNode *ColorNodeStack::pop()
{
   return((const ColorNode *)mStack.pop());
}
