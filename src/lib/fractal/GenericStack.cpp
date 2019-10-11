// C/C++ headers

#include <stdlib.h>

#include "GenericStack.h"
#include "cpp_assert.h"
#include "dmemory.h"

/*****************************************************************************
 * Declaration of private class: StackEntry
 *****************************************************************************/

class StackEntry
{
   public:
      StackEntry(void *data);
      void *getData() const;
      void setNext(StackEntry *next);
      void setPrevious(StackEntry *previous);
      StackEntry *getNext() const;
      StackEntry *getPrevious() const;

   private:
      StackEntry(const StackEntry &other);
      StackEntry &operator=(const StackEntry &other);
      void *mData;
      StackEntry *mNext;
      StackEntry *mPrevious;
};

/*****************************************************************************
 * Definition of private class: StackEntry
 *****************************************************************************/

StackEntry::StackEntry(void *data)
   :
   mData(data),
   mNext(NULL),
   mPrevious(NULL)
{
   // Nothing to do
}

void *StackEntry::getData() const
{
   return(mData);
}

void StackEntry::setNext(StackEntry *next)
{
   mNext = next;
}

void StackEntry::setPrevious(StackEntry *previous)
{
   mPrevious = previous;
}

StackEntry *StackEntry::getNext() const
{
   return(mNext);
}

StackEntry *StackEntry::getPrevious() const
{
   return(mPrevious);
}

/*****************************************************************************
 * Definition of class: GenericStack
 *****************************************************************************/

GenericStack::GenericStack()
   :
   mTail(NULL),
   mCount(0)
{
   // Nothing to do
}

GenericStack::~GenericStack()
{
   StackEntry *index = mTail;

   while(index)
   {
      mTail = index->getNext();
      DDELETE(index);
      index = mTail;
   }
}

int GenericStack::isEmpty() const
{
   return(mCount == 0);
}

void *GenericStack::pop()
{
   CPP_ASSERT(mTail != NULL);

   void *data          = mTail->getData();
   StackEntry *newTail = mTail->getPrevious();
   DDELETE(mTail);

   if(newTail)
      newTail->setNext(NULL);

   mTail = newTail;

   --mCount;

   return(data);
}

void *GenericStack::top()
{
   CPP_ASSERT(mTail != NULL);

   return(mTail->getData());
}

void GenericStack::push(void *data)
{
   StackEntry *newEntry = 0;

   DNEW(newEntry, StackEntry(data));

   if(mTail)
   {
      mTail->setNext(newEntry);
      newEntry->setPrevious(mTail);
   }

   ++mCount;

   mTail = newEntry;
}

int GenericStack::size() const
{
   return(mCount);
}
