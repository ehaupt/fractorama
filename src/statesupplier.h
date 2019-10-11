#ifndef _STATE_SUPPLIER_H_
#   define _STATE_SUPPLIER_H_

class State;

class StateSupplier
{
   public:
      virtual State *getState() = 0;
};
   
#endif
