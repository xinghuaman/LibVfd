#include <Bounce2.h>
#include "DvdVfd.h"
#include <AbstractVFD.h>
#include <DigWriteShifter.h>
#include <AnotherMultiplexer.h>
#include <MirroringBitManipulator.h>
#include <LarsonScanner.h>
#include <MemoryFree.h>
#include <VfdController.h>
#include <EqualsLikeCommandParser.h>
#include <CommandAssembler.h>

#define COMMANDBUFSIZE 50
#define DEBOUNCE_TIME 100
#define BAUD_RATE 9600
#define ANIMATION_TIME_MS 100
#define CYCLE_TIME_MS 2

const int dataPin = 2;
const int latchPin = 3;
const int clockPin = 4;
const int testPin = 9;

MirroringBitManipulator manipulator;
DigWriteShifter shifter;
DvdVfd anotherVFD;
AnotherMultiplexer plexi(&shifter, anotherVFD.getBins(), 4);
Bounce debouncer;
VfdController controller;
CommandAssembler assembler;

boolean pinState13=false;
unsigned long lasttime1;
unsigned long lasttime2;
boolean lightShowState=false;
char buffer0[COMMANDBUFSIZE];
char buffer1[COMMANDBUFSIZE];

void setup() {
  
  Serial.begin(BAUD_RATE);
  assembler.setBuffer(buffer0, COMMANDBUFSIZE);

  manipulator.setMirroring(0x01,20);
  shifter.begin(dataPin,latchPin,clockPin,&manipulator);
  pinMode(13,OUTPUT);
  pinMode(testPin, INPUT_PULLUP);
  debouncer.attach(testPin);
  debouncer.interval(DEBOUNCE_TIME);

  controller.begin(&anotherVFD);
   
}      

void loop(){
  debouncer.update();
  assembler.addChar(Serial.read());

  if (debouncer.fell()) {
    lightShowState = !lightShowState;
    controller.enableLightShow(lightShowState);
    if (lightShowState) anotherVFD._tdvd.setBlink(); else anotherVFD._tdvd.setEnabled(false);
  }
 
  if (assembler.isCommandAvailable()) {
    assembler.getCommand(buffer1,COMMANDBUFSIZE);
    controller.obey(buffer1);
  }
  
  if (millis() - lasttime2 > ANIMATION_TIME_MS) {
  	anotherVFD.animate();
    	digitalWrite(13,pinState13);
    	pinState13=~pinState13;
    	controller.animate();
  	lasttime2 = millis();
  }
  
  if (millis()-lasttime1 > CYCLE_TIME_MS) {
  	plexi.cycle();
	lasttime1 = millis();
  }

  

}
