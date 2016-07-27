#include "SevenSegmentEncoder.h"

void SevenSegmentEncoder::begin(byte radix, String memonic) {
   AnimatableFunction::begin(memonic);
  _radix = radix;
};

void SevenSegmentEncoder::addSegment(SevenSegments* segment, unsigned long* bin){
  _mySegments[_numSegments]=segment;
  _myBins[_numSegments]=bin;
  _numSegments++;
}

void SevenSegmentEncoder::encode(int number) {
  Serial.print("Trying to encode: ");
  Serial.println(number);
  if (number < 0 ) {
    number = -number;
    //TODO: Handle numbersign.
  }
  
  for (int i=_numSegments-1; i>=0; i--) {
    Serial.println(i);
    byte digit = number % _radix;
    number = number / _radix;
    (*_myBins[i])&=~_mySegments[i]->getMaskForClearing();
    (*_myBins[i])|=_mySegments[i]->getMaskForDigit(digit);
  }
  //TODO: Handle overflow
};

void SevenSegmentEncoder::animate() {
  //TODO: Blink the Number?
}

void SevenSegmentEncoder::setEnabled(boolean enabled) {
  AnimatableFunction::setEnabled(enabled);
  if (enabled) {
    encode(0);
  } else {
    for (int i=_numSegments-1; i>=0; i--) {
    	(*_myBins[i])&=~_mySegments[i]->getMaskForClearing();
    }
  }
}

String SevenSegmentEncoder::getType() {
  return "SevenSegmentEncoder";
}
