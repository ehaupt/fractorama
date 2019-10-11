#include "ComplexNodeStack.h"

int ComplexNodeStack::isEmpty() const
{
   return(mStack.isEmpty());
}

void ComplexNodeStack::push(const ComplexNode *ptr)
{
   mStack.push((void *)ptr);
}

const ComplexNode *ComplexNodeStack::pop()
{
   return((const ComplexNode *)mStack.pop());
}

const ComplexNode *ComplexNodeStack::top()
{
   return((const ComplexNode *)mStack.top());
}
