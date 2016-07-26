#include "AnotherMultiplexer.h"

AnotherMultiplexer::AnotherMultiplexer(Shifter* shifter, unsigned long* bins, byte numBins){
   _shifter = shifter;
   _bins = bins;
   _numBins = numBins;
};

void AnotherMultiplexer::cycle() {
  unsigned long toWrite = _bins[_currentBin++];
  
  _shifter->write(toWrite);
  if (_currentBin >= _numBins) _currentBin = 0;
}
