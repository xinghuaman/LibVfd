#include "DigWriteShifter.h"

#include <Arduino.h>

void DigWriteShifter::begin(int dataPin, int latchPin, int clockPin, BitManipulator* manipulator){
  _dataPin = dataPin;
  _latchPin = latchPin;
  _clockPin = clockPin;
  _manipulator = manipulator;

  pinMode(_dataPin,OUTPUT);
  pinMode(_latchPin,OUTPUT);
  pinMode(_clockPin, OUTPUT);

}

void DigWriteShifter::write(unsigned long toWrite){
 
     if (_manipulator != NULL)
     	toWrite=_manipulator->manipulate(toWrite);
  
     digitalWrite(_latchPin,LOW);
     for (int i=3;i>=0;i--){
       byte theByte = (byte) (toWrite >> (i*8));
       shiftOut(_dataPin, _clockPin, MSBFIRST, theByte);
     }
     digitalWrite(_latchPin, HIGH);
 
}
