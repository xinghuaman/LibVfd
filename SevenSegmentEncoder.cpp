#include "SevenSegmentEncoder.h"
#include <avr/pgmspace.h>

void SevenSegmentEncoder::begin(byte radix, const char* const memonic) {
   AnimatableFunction::begin(memonic);
  _radix = radix;
  _overflow = NULL;
  _minus = NULL;
};

void SevenSegmentEncoder::addSegment(SevenSegments* segment, unsigned long* bin){
  _mySegments[_numSegments]=segment;
  _myBins[_numSegments]=bin;
  _numSegments++;
}

void SevenSegmentEncoder::encode(int number) {
  //Serial.print("Trying to encode: ");
  //Serial.println(number);

  if (_minus != NULL) _minus->setEnabled(number < 0);
  if (number < 0) number = -number;
  
  for (int i=_numSegments-1; i>=0; i--) {
    //Serial.println(i);
    byte digit = number % _radix;
    number = number / _radix;
    (*_myBins[i])&=~_mySegments[i]->getMaskForClearing();
    (*_myBins[i])|=_mySegments[i]->getMaskForDigit(digit);
  }
  
  if (_overflow != NULL) _overflow->setEnabled(number > 0);
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

const char* SevenSegmentEncoder::getRawType() {
	return txt_SevenSegmentEncoder;
}

void SevenSegmentEncoder::setOverflow(AnimatableFunction* overflow) {
	_overflow=overflow;
}

void SevenSegmentEncoder::setMinus(AnimatableFunction* minus) {
	_minus=minus;
}
