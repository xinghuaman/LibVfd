#ifndef AnimatableFunction_h
#define AnimatableFunction_h

#include <Arduino.h>

class AnimatableFunction {
  private:
    String _memonic;
    unsigned long _mask;
    boolean _blink;
    
  public:
    virtual void begin(String memonic);
    virtual String getMemonic();
    virtual void animate()=0;
    virtual void setEnabled(boolean enabled);
    virtual void setBlink();
    virtual boolean isBlink();
};
#endif
