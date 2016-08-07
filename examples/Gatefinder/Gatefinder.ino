#include <InvertingBitManipulator.h>
#include <Shifter.h>
#include <LightSwitchCallback.h>

InvertingBitManipulator inverter;

Shifter shifter;

void setup() {
	Serial.begin(9600);
	inverter.begin(0xFFFFFFFF);
	shifter.begin(2,3,4,&inverter);
}

void loop() {
   if (Serial.available()>0) {
       String stringcoming = Serial.readString();
       unsigned long incoming = strtoul(stringcoming.c_str(),NULL,16);
  
       shifter.write(incoming);

    }
}
