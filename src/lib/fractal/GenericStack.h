#ifndef _GENERIC_STACK_H_
#   define _GENERIC_STACK_H_

class StackEntry;

class GenericStack
{
   public:
      GenericStack();
      ~GenericStack();
      int isEmpty() const;
      void *top();
      void *pop();
      void push(void *);
      int size() const;

   private:
      StackEntry *mTail;
      int mCount;
};

#endif
