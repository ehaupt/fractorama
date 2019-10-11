#ifndef _COLOR_TABLE_H_
#   define _COLOR_TABLE_H_

#include <iostream>

using std::ostream;

class ColorTable
{
   public:
      ColorTable();
      ~ColorTable();

   private:
      ColorTable(const ColorTable &other);
      ColorTable &operator=(const ColorTable &other);

   public:
      void setCurrentIndex(int index);
      void addEntry(int red, int green, int blue);

      void lookup(
         int index,
         int *redPtr,
         int *greenPtr,
         int *bluePtr,
         int *invalidLookupCountPtr
      ) const;
      friend ostream &operator<<(ostream &out, const ColorTable &theTable);

   private:
      void ensureCapacity();
      int mCurrentIndex;
      int mTableSize;
      int **mEntries;
      enum { RED, GREEN, BLUE };
      enum { BLOCK_SIZE = 256 };
};

#endif
