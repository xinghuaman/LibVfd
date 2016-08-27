#ifndef AnimatableFunction_h
#define AnimatableFunction_h

#include <avr/pgmspace.h>

class AnimatableFunction {
  private:
    char* _memonic;
    unsigned long _mask;
    bool _blink;
    
  public:
    virtual int getRawType();
    virtual void begin(const char * const memonic);
    virtual void getMemonic(char* buffer, int bufsize);
    virtual bool hasMemonic(char* buffer);
    virtual void animate()=0;
    virtual void setEnabled(bool enabled);
    virtual void setBlink();
    virtual bool isBlink();
};
#endif
