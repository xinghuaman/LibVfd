#ifndef AnimatableFunction_h
#define AnimatableFunction_h

#include <avr/pgmspace.h>

const char txt_AnimatableFunction[] PROGMEM = "AnimatableFunction";

class AnimatableFunction {
  private:
    char* _memonic;
    unsigned long _mask;
    bool _blink;
    
  public:
    virtual void getType(char* buffer);
    virtual void begin(const char * const memonic);
    virtual void getMemonic(char* buffer);
    virtual void animate()=0;
    virtual void setEnabled(bool enabled);
    virtual void setBlink();
    virtual bool isBlink();
};
#endif
