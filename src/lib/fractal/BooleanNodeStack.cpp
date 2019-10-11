#include "BooleanNodeStack.h"

int BooleanNodeStack::isEmpty() const
{
   return(mStack.isEmpty());
}

int BooleanNodeStack::size() const
{
   return(mStack.size());
}

void BooleanNodeStack::push(const BooleanNode *ptr)
{
   mStack.push((void *)ptr);
}

const BooleanNode *BooleanNodeStack::pop()
{
   return((const BooleanNode *)mStack.pop());
}
