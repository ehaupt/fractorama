#include "SwitchStatementStack.h"

void SwitchStatementStack::push(const SwitchStatement *ptr)
{
   mStack.push((void *)ptr);
}

const SwitchStatement *SwitchStatementStack::pop()
{
   return((SwitchStatement *)mStack.pop());
}

SwitchStatement *SwitchStatementStack::top()
{
   return((SwitchStatement *)mStack.top());
}
