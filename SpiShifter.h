#ifndef SpiShifter_h
#define SpiShifter_h

#include "BitManipulator.h"
#include "Shifter.h"
/**
 * The SpiShifter is to transport data to a 74xx595 latching
 * shift register. It can do 'last-minute' transformations
 * to the data by filtering it through an optional bit-
 * manipulator.
 */
class SpiShifter : public Shifter{
  private:
    BitManipulator* _manipulator;
    
  public:
    void begin(BitManipulator* manipulator);
    void write(unsigned long);
};
#endif 
