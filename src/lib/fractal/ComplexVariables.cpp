// C/C++ Headers

#include <string.h>

// Local Headers

#include "ComplexVariables.h"
#include "tf.h"
#include "dmemory.h"

/*****************************************************************************
 * File-level constant(s)
 *****************************************************************************/

const dcomplex ComplexVariables::ZERO(0.0, 0.0);

/*****************************************************************************
 * Declaration of private struct 'ComplexEntry'
 *****************************************************************************/

struct ComplexEntry
{
   ComplexEntry(const char *name);
   ~ComplexEntry();

   char *mName;
   dcomplex mValue;

   ostream &print(ostream &out) const;
};

ostream &operator<<(ostream &out, const ComplexEntry &entry);


/*****************************************************************************
 * Definition of private struct 'ComplexEntry'
 *****************************************************************************/

ComplexEntry::ComplexEntry(const char *name) : mName(0)
{
   DNEW(mName, char[strlen(name) + 1]);
   strcpy(mName, name);
}

ComplexEntry::~ComplexEntry()
{
   DADELETE(mName);
}

ostream &ComplexEntry::print(ostream &out) const
{
   out << mName << " = [" << __REAL(mValue) << ", " << __IMAG(mValue) << "]";
   return(out);
}

ostream &operator<<(ostream &out, const ComplexEntry &entry)
{
   return(entry.print(out));
}

/*****************************************************************************
 * Definition of class 'ComplexVariables'
 *****************************************************************************/

ComplexVariables::ComplexVariables() :
   mCount(0),
   mEntries(0)
{
}

ComplexVariables::~ComplexVariables()
{
   for(int i = 0; i < mCount; i ++)
      DDELETE(mEntries[i]);

   DADELETE(mEntries);
}

dcomplex * ComplexVariables::assign(const char *name)
{
   dcomplex *ptr = lookup(name);

   if(ptr == NULL)
   {
      ComplexEntry **newEntries = 0;
      DNEW(newEntries, ComplexEntry *[mCount + 1]);

      for(int i = 0; i < mCount; i ++)
         newEntries[i] = mEntries[i];

      DNEW(newEntries[mCount], ComplexEntry(name));

      if(mEntries)
         DADELETE(mEntries);

      mEntries = newEntries;
      ptr      = &(mEntries[mCount++]->mValue);
   }

   return(ptr);
}

dcomplex *ComplexVariables::lookup(const char *name) const
{
   for(int i = 0; i < mCount; i ++)
      if(strcmp(name, mEntries[i]->mName) == 0)
         return(&(mEntries[i]->mValue));

   return(NULL);
}

void ComplexVariables::initialize()
{
   for(int i = 0; i < mCount; i ++)
      mEntries[i]->mValue = ZERO;
}

ostream &ComplexVariables::print(ostream &out) const
{
   for(int i = 0; i < mCount; i ++)
   {
      if(i > 0)
         out << "\n";

      out << "entry[" << i << "]" << " => ";
      mEntries[i]->print(out);
   }

   return(out);
}

ostream &operator<<(ostream &out, const ComplexVariables &cv)
{
   return(cv.print(out));
}
