#ifndef _QINFINITE_LOOP_CALLBACK_H_
#   define _QINFINITE_LOOP_CALLBACK_H_

#include "InfiniteLoopCallback.h"

class QObject;

class QInfiniteLoopCallback : public InfiniteLoopCallback
{
   public:
      QInfiniteLoopCallback(int *abortFlag);
      int abortProcessing();

   private:
      int *mAbortFlag;
};

#endif
