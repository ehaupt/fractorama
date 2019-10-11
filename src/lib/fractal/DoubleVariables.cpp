#include <string.h>

// Local Headers

#include "DoubleVariables.h"
#include "tf.h"
#include "dmemory.h"

ostream &operator<<(ostream &out, const DoubleEntry &entry);

/*****************************************************************************
 * Initialize static member variables
 *****************************************************************************/

const double DoubleVariables::ZERO = 0.0;

/*****************************************************************************
 * Declaration of private struct 'DoubleEntry'
 *****************************************************************************/

struct DoubleEntry
{
   DoubleEntry(const char *name);
   ~DoubleEntry();

   char *mName;
   double mValue;

   ostream &print(ostream &out) const;
};

/*****************************************************************************
 * Definition of private struct 'DoubleEntry'
 *****************************************************************************/

DoubleEntry::DoubleEntry(const char *name) : mName(0)
{
   DNEW(mName, char[strlen(name) + 1]);
   strcpy(mName, name);
}

DoubleEntry::~DoubleEntry()
{
   DADELETE(mName);
}

ostream &DoubleEntry::print(ostream &out) const
{
   out << mName << " = [" << mValue << "]";
   return(out);
}

ostream &operator<<(ostream &out, const DoubleEntry &entry)
{
   return(entry.print(out));
}

/*****************************************************************************
 * Definition of class 'DoubleVariables'
 *****************************************************************************/

DoubleVariables::DoubleVariables() :
   mCount(0),
   mEntries(0)
{
}

DoubleVariables::~DoubleVariables()
{
   for(int i = 0; i < mCount; i ++)
      DDELETE(mEntries[i]);

   DADELETE(mEntries);
}

double *DoubleVariables::assign(const char *name)
{
   double *ptr = lookup(name);

   if(ptr == NULL)
   {
      DoubleEntry **newEntries = 0;
      DNEW(newEntries, DoubleEntry *[mCount + 1]);

      for(int i = 0; i < mCount; i ++)
         newEntries[i] = mEntries[i];

      DNEW(newEntries[mCount], DoubleEntry(name));

      if(mEntries)
         DADELETE(mEntries);

      mEntries = newEntries;

      ptr = &(mEntries[mCount++]->mValue);
   }

   return(ptr);
}

double * DoubleVariables::lookup(const char *name) const
{
   for(int i = 0; i < mCount; i ++)
      if(strcmp(name, mEntries[i]->mName) == 0)
         return(&(mEntries[i]->mValue));

   return(NULL);
}

void DoubleVariables::initialize()
{
   for(int i = 0; i < mCount; i ++)
      mEntries[i]->mValue = ZERO;
}

ostream &DoubleVariables::print(ostream &out) const
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

ostream &operator<<(ostream &out, const DoubleVariables &dv)
{
   return(dv.print(out));
}
