#include <InvertingBitManipulator.h>
#include <Shifter.h>
#include <LightSwitchCallback.h>
#include <MemoryFree.h>
#include <EqualsLikeCommandParser.h>

InvertingBitManipulator inverter;
Shifter shifter;

unsigned long incoming;
unsigned long lasttime;
bool showincoming = true;

void setup() {
	Serial.begin(9600);
	inverter.begin(0xFFFFFFFF);
	shifter.begin(2,3,4,&inverter);
        lasttime = millis();
}



void loop() {
   if (Serial.available()>0) {
       String stringcoming = Serial.readString();
       incoming = strtoul(stringcoming.c_str(),NULL,16);
       lasttime = 0;
       showincoming = true;
    }
    if (millis() - lasttime > 1000) {
      unsigned long toShow = showincoming ? incoming : 0x00;
      shifter.write(toShow);
      Serial.println(toShow,HEX);
      
      showincoming = !showincoming;
      lasttime = millis();
    }
   
}
