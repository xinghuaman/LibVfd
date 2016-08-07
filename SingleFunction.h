#ifndef SingleFunction_h
#define SingleFunction_h

#include "AnimatableFunction.h"

class SingleFunction : public AnimatableFunction {
  private:
    unsigned long* _bin;
    unsigned long _mask;
    
  public:
    virtual void begin(unsigned long* bin, unsigned long mask, const char * const memonic);
    virtual void animate();
    virtual void setEnabled(bool enabled);
};
#endif
