#ifndef SingleFunction_h
#define SingleFunction_h

#include "AnimatableFunction.h"
#include <Arduino.h>

class SingleFunction : public AnimatableFunction {
  private:
    unsigned long* _bin;
    unsigned long _mask;
    
  public:
    virtual void begin(unsigned long*, unsigned long mask, String memonic);
    virtual void animate();
    virtual void setEnabled(boolean enabled);
};
#endif
