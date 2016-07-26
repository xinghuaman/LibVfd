#ifndef AnotherMultiplexer_h
#define AnotherMultiplexer_h

#include "Shifter.h"
#include <Arduino.h>

class AnotherMultiplexer {
  private:
    Shifter* _shifter;
    unsigned long* _bins;
    byte _currentBin;
    byte _numBins;
    
    
  public:
    AnotherMultiplexer(Shifter* shifter, unsigned long* bins, byte numBins);
    void cycle();
};

#endif
