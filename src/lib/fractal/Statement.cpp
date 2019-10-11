// Local Headers

#include "Statement.h"

Statement::Statement()
{
}

Statement::~Statement()
{
}

ostream &operator<<(ostream &out, const Statement &s)
{
   return(s.print(out));
}
