#ifndef _INFINITE_LOOP_CALLBACK_H_
#   define _INFINITE_LOOP_CALLBACK_H_

class InfiniteLoopCallback
{
   public:
      typedef enum { ABORTED, NOT_ABORTED } CurrentState;

      virtual ~InfiniteLoopCallback() {}
      static const int NITERATIONS;
      virtual int abortProcessing();
};

#endif
