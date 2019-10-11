#include "RegionNodeStack.h"

int RegionNodeStack::isEmpty() const
{
   return(mStack.isEmpty());
}

void RegionNodeStack::push(const RegionNode *ptr)
{
   mStack.push((void *)ptr);
}

const RegionNode *RegionNodeStack::pop()
{
   return((const RegionNode *)mStack.pop());
}
