#ifndef _FRACTAL_OBSERVER_H_
#   define _FRACTAL_OBSERVER_H_

class FractalObserver
{
   public:
      virtual void percentComplete(double percentage)            = 0;
      virtual void drawingStarted()                              = 0;
      virtual void drawingFinished(char *text, int wasCancelled) = 0;
      virtual void zoomAllowed()                                 = 0;
      virtual void zoomNotAllowed()                              = 0;
};
   
#endif // FRACTAL_OBSERVER_H_
