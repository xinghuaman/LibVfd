#include "SpiShifter.h"

#include <SPI.h>

#define SpiShifter_mosi 11
#define SpiShifter_sck 13
#define SpiShifter_ss 10
#define SpiShifter_latchPin 2

void SpiShifter::begin(BitManipulator* manipulator){
  _manipulator = manipulator;

  pinMode(SpiShifter_mosi, OUTPUT);
  pinMode(SpiShifter_sck, OUTPUT);
  pinMode(SpiShifter_ss, OUTPUT);
  pinMode(SpiShifter_latchPin, OUTPUT);

  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.begin();
}

void SpiShifter::write(unsigned long toWrite){
 
     if (_manipulator != NULL)
     	toWrite=_manipulator->manipulate(toWrite);
  
     //digitalWrite(SpiShifter_latchPin,LOW);
     digitalWrite(SpiShifter_ss,LOW);
     for (int i=3;i>=0;i--){
       byte theByte = (byte) (toWrite >> (i*8));
       SPI.transfer(theByte);
     }
     //digitalWrite(SpiShifter_latchPin, HIGH);
     digitalWrite(SpiShifter_ss, HIGH);

 
}
