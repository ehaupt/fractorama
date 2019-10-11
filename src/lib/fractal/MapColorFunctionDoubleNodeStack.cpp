#include "MapColorFunctionDoubleNodeStack.h"

int MapColorFunctionDoubleNodeStack::isEmpty() const
{
   return(mStack.isEmpty());
}

int MapColorFunctionDoubleNodeStack::size() const
{
   return(mStack.size());
}

void MapColorFunctionDoubleNodeStack::push(
   const MapColorFunctionDoubleNode *ptr
)
{
   mStack.push((void *)ptr);
}

const MapColorFunctionDoubleNode *MapColorFunctionDoubleNodeStack::pop()
{
   return((const MapColorFunctionDoubleNode *)mStack.pop());
}

MapColorFunctionDoubleNode *MapColorFunctionDoubleNodeStack::top()
{
   return((MapColorFunctionDoubleNode *)mStack.top());
}
