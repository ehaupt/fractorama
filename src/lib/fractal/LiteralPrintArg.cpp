// C/C++ Headers

#include <string.h>

// Local Headers

#include "LiteralPrintArg.h"
#include "dmemory.h"

LiteralPrintArg::LiteralPrintArg(char *theString) :
   mString(0)
{
   int length = strlen(theString);

   DNEW(mString, char[length + 1]);

   int flag   = 0;
   int j      = 0;

   // Convert '\' followed by 'n' to '\n' ...

   for(int i = 0; theString[i]; i ++)
   {
      char c = theString[i];

      if(flag)
      {
         if(c != 'n')
         {
            mString[j++] = '\\';
            mString[j++] = c;
         }
         else
            mString[j++] = '\n';

         flag = 0;
      }
      else
      {
         if(c == '\\')
            flag = 1;
         else
            mString[j++] = c;
      }
   }

   if(flag)
      mString[j++] = '\\';

   mString[j] = '\0';
}

LiteralPrintArg::~LiteralPrintArg()
{
   DADELETE(mString);
}

void LiteralPrintArg::execute(ostream &out) const
{
   out << mString;
}

ostream &LiteralPrintArg::print(ostream &out) const
{
   // Here we output '\n' as '\' and 'n'

   out << "\"";

   for(int i = 0; mString[i]; i ++)
   {
      if(mString[i] == '\n')
         out << "\\n";

      else
         out << mString[i];
   }

   return(out << "\"");
}
