#ifndef Shifter_h
#define Shifter_h

/**
 * The Shifter is to transport data to a 74xx595 latching
 * shift register. It can do 'last-minute' transformations
 * to the data by filtering it through an optional bit-
 * manipulator.
 */
class Shifter {
  public:
    virtual void write(unsigned long) = 0;
};
#endif 
