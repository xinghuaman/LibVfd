#ifndef Shifter_h
#define Shifter_h

#include "BitManipulator.h"

class Shifter {
  private:
    int _dataPin;
    int _latchPin;
    int _clockPin;
    BitManipulator* _manipulator;
    
  public:
    void begin(int dataPin, int latchPin, int clockPin, BitManipulator* manipulator);
    void write(unsigned long);
};
#endif 
