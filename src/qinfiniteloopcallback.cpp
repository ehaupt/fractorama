// Qt Headers

#include <qapplication.h>

// Local Headers

#include "qinfiniteloopcallback.h"

QInfiniteLoopCallback::QInfiniteLoopCallback(int *abortFlag) :
   mAbortFlag(abortFlag)
{
}

int QInfiniteLoopCallback::abortProcessing()
{
   qApp->processEvents();
   return(*mAbortFlag);
}
