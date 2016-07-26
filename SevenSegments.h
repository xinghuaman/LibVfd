#ifndef SevenSegments_h
#define SevenSegments_h

#include "Arduino.h"

class SevenSegments {
  private:
    unsigned long _masks[0xF];
    unsigned long _middle;
    unsigned long _decimalPoint;
  
  public:
    void begin(
       unsigned long top,
       unsigned long topLeft,
       unsigned long topRight,
       unsigned long middle,
       unsigned long bottomLeft,
       unsigned long bottomRight,
       unsigned long bottom,
       unsigned long decimalPoint
     );
     
    unsigned long getMaskForDigit(byte digit);
    unsigned long getMaskForClearing();
};

#endif
