#ifndef DigWriteShifter_h
#define DigWriteShifter_h

#include "BitManipulator.h"
#include "Shifter.h"
/**
 * The DigWriteShifter is to transport data to a 74xx595 latching
 * shift register. It can do 'last-minute' transformations
 * to the data by filtering it through an optional bit-
 * manipulator.
 */
class DigWriteShifter : public Shifter {
  private:
    int _dataPin;
    int _latchPin;
    int _clockPin;
    BitManipulator* _manipulator;
    
  public:
    void begin(int dataPin, int latchPin, int clockPin, BitManipulator* manipulator);
    virtual void write(unsigned long);
};
#endif 
