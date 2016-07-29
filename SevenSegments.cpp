#include "SevenSegments.h"
#include "Arduino.h"

void SevenSegments::begin (
       unsigned long top,
       unsigned long topLeft,
       unsigned long topRight,
       unsigned long middle,
       unsigned long bottomLeft,
       unsigned long bottomRight,
       unsigned long bottom,
       unsigned long decimalPoint
     ) {
     _middle = middle;
     _decimalPoint = decimalPoint;
     _masks[0x00] = top | topLeft | bottomLeft | bottom | bottomRight | topRight;
     _masks[0x01] = topRight | bottomRight;
     _masks[0x02] = top | topRight | middle | bottomLeft | bottom;
     _masks[0x03] = top | topRight | middle | bottomRight | bottom;
     _masks[0x04] = topLeft | topRight | middle | bottomRight;
     _masks[0x05] = top | topLeft | middle | bottomRight | bottom;
     _masks[0x06] = top | topLeft | middle | bottomRight | bottom | bottomLeft;
     _masks[0x07] = top | topRight | bottomRight;
     _masks[0x08] = top | topRight |  middle | bottomRight | bottom | bottomLeft | topLeft;
     _masks[0x09] = top | topRight |  middle | bottom | bottomRight | topLeft; 
};

unsigned long SevenSegments::getMaskForDigit(byte digit) {
  //Serial.print("Mask for Digit: ");
  //Serial.println(digit);
  if (digit > 10) return 0L;
  unsigned long ret = _masks[digit];
  return ret;
};

unsigned long SevenSegments::getMaskForClearing(){
  return _masks[8] | _decimalPoint;
}


