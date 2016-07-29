#ifndef CountingLightShow_h
#define CoutingLightShow_h

#include "SevenSegmentEncoder.h"
#include <Arduino.h>

class CountingLightShow {
  private:
    unsigned long _counters[20];
    SevenSegmentEncoder* _digits[20];
    int _numDigits;
    boolean _enabled;


  public:
    CountingLightShow();
    void addDigit(SevenSegmentEncoder* encoder, int initialCount);
    void animate();
    void enable(boolean enabled);


};

#endif
