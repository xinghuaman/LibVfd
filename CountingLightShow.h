#ifndef CountingLightShow_h
#define CountingLightShow_h

#include "SevenSegmentEncoder.h"
#include <Arduino.h>

#define COUNTINGLIGHTSHOW_MAXDIGITS 10

class CountingLightShow {
  private:
    unsigned long _counters[COUNTINGLIGHTSHOW_MAXDIGITS];
    SevenSegmentEncoder* _digits[COUNTINGLIGHTSHOW_MAXDIGITS];
    int _numDigits;
    boolean _enabled;


  public:
    CountingLightShow();
    void addDigit(SevenSegmentEncoder* encoder, int initialCount);
    void animate();
    void enable(boolean enabled);


};

#endif
