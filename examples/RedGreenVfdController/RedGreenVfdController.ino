#include <Bounce2.h>
#include "RedGreenVcrVfd.h"
#include <AbstractVFD.h>
#include <Shifter.h>
#include <SpiShifter.h>
#include <AnotherMultiplexer.h>
#include <MirroringBitManipulator.h>
#include <CountingLightShow.h>
#include <LarsonLightShowBuilder.h>
#include <LightSwitchCallback.h>
#include <MemoryFree.h>
#include <VfdController.h>
#include <EqualsLikeCommandParser.h>
#include <CommandAssembler.h>
#include <TimerOne.h>
#include <SPI.h>

#define COMMANDBUFSIZE 20
#define DEBOUNCE_TIME 100
#define BAUD_RATE 9600
#define ANIMATION_TIME_MS 100
#define CYCLE_TIME_MUS 2000

const int dataPin = 2;
const int latchPin = 3;
const int clockPin = 4;
const int testPin = 9;

SpiShifter shifter;
RedGreenVcrVfd vfd;
AnotherMultiplexer plexi(&shifter, vfd.getBins(), vfd.getNumBins());
Bounce debouncer;
VfdController controller;
CommandAssembler assembler;

unsigned long lasttime;
boolean lightShowState=false;
char buffer0[COMMANDBUFSIZE];
char buffer1[COMMANDBUFSIZE];

void timeOut() {
	plexi.cycle();
}


void setup() {
  
  Serial.begin(BAUD_RATE);
  assembler.setBuffer(buffer0, COMMANDBUFSIZE);

  Timer1.initialize(CYCLE_TIME_MUS);
  Timer1.attachInterrupt(timeOut);

  shifter.begin(NULL);
  pinMode(testPin, INPUT_PULLUP);
  debouncer.attach(testPin);
  debouncer.interval(DEBOUNCE_TIME);
  controller.begin(&vfd);
}      

void loop(){
  debouncer.update();
  assembler.addChar(Serial.read());

  if (debouncer.fell()) {
    lightShowState = !lightShowState;
    controller.enableLightShow(lightShowState);
    Serial.println(F("LightShow!"));
  }
 
  if (assembler.isCommandAvailable()) {
    Serial.println(F("Command Avail!"));
    assembler.getCommand(buffer1,COMMANDBUFSIZE);
    controller.obey(buffer1);
  }
  
  if (millis() - lasttime > ANIMATION_TIME_MS) {
  	vfd.animate();
	controller.animate();
  	lasttime = millis();
  }
  
}
