#include "DoubleNodeStack.h"

int DoubleNodeStack::isEmpty() const
{
   return(mStack.isEmpty());
}

void DoubleNodeStack::push(const DoubleNode *ptr)
{
   mStack.push((void *)ptr);
}

const DoubleNode *DoubleNodeStack::pop()
{
   return((const DoubleNode *)mStack.pop());
}

const DoubleNode *DoubleNodeStack::top()
{
   return((const DoubleNode *)mStack.top());
}
