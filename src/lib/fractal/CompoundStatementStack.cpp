#include "CompoundStatementStack.h"

int CompoundStatementStack::isEmpty() const
{
   return(mStack.isEmpty());
}

int CompoundStatementStack::size() const
{
   return(mStack.size());
}

void CompoundStatementStack::push(const CompoundStatement *ptr)
{
   mStack.push((void *)ptr);
}

const CompoundStatement *CompoundStatementStack::pop()
{
   return((CompoundStatement *)mStack.pop());
}

CompoundStatement *CompoundStatementStack::top()
{
   return((CompoundStatement *)mStack.top());
}
