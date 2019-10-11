#include <stdlib.h>

#include "ColorTable.h"
#include "dmemory.h"

ColorTable::ColorTable() : mCurrentIndex(0), mTableSize(0), mEntries(0)
{
}

ColorTable::~ColorTable()
{
   for(int i = 0; i < mTableSize; i ++)
   {
      DADELETE(mEntries[i]);
   }

   if(mEntries)
      DADELETE(mEntries);
}

void ColorTable::setCurrentIndex(int index)
{
   mCurrentIndex = index;
}

void ColorTable::addEntry(int red, int green, int blue)
{
   ensureCapacity();

   if(!mEntries[mCurrentIndex])
   {
      DNEW(mEntries[mCurrentIndex], int[3]);
   }

   mEntries[mCurrentIndex][RED]   = red;
   mEntries[mCurrentIndex][GREEN] = green;
   mEntries[mCurrentIndex][BLUE]  = blue;

   mCurrentIndex++;
}

void ColorTable::lookup(
   int index,
   int *redPtr,
   int *greenPtr,
   int *bluePtr,
   int *invalidColorLookupPtr
) const
{
   if(index < 0 || index >= mTableSize || !mEntries[index])
   {
      (*invalidColorLookupPtr)++;

      *redPtr = *greenPtr = *bluePtr = 0;
   }
   else
   {
      *redPtr   = mEntries[index][RED];
      *greenPtr = mEntries[index][GREEN];
      *bluePtr  = mEntries[index][BLUE];
   }
}

ostream &operator<<(ostream &out, const ColorTable &theTable)
{
   int first = 1;

   for(int i = 0; i < theTable.mTableSize; i ++)
   {
      if(theTable.mEntries[i])
      {
         if(first)
            first = 0;
         else
            out << "\n";

         out << "entry[" << i << "] (" <<
            theTable.mEntries[i][ColorTable::RED]   << ", " <<
            theTable.mEntries[i][ColorTable::GREEN] << ", " <<
            theTable.mEntries[i][ColorTable::BLUE]  << ")";
      }
   }

   return(out);
}

void ColorTable::ensureCapacity()
{
   int newSize = mTableSize;

   while(mCurrentIndex >= newSize)
      newSize += BLOCK_SIZE;

   if(newSize != mTableSize)
   {
      int **newEntries = 0;

      DNEW(newEntries, int *[newSize]);

      for(int i = 0; i < newSize; i ++)
         newEntries[i] = (i < mTableSize ? mEntries[i] : 0);

      DADELETE(mEntries);

      mTableSize = newSize;
      mEntries   = newEntries;
      
   }
}
