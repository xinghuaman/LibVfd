#include <Bounce2.h>
#include "RedGreenVcrVfd.h"
#include <AbstractVFD.h>
#include <Shifter.h>
#include <AnotherMultiplexer.h>
#include <MirroringBitManipulator.h>
#include <CountingLightShow.h>
#include <LarsonLightShowBuilder.h>
#include <LarsonScanner.h>
#include <LightSwitchCallback.h>
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

Shifter shifter;
RedGreenVcrVfd vfd;
AnotherMultiplexer plexi(&shifter, vfd.getBins(), vfd.getNumBins());
//CountingLightShow show1;
//LarsonScanner* show2;
//LarsonLightShowBuilder show2builder;
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

  shifter.begin(dataPin,latchPin,clockPin,NULL);
  pinMode(13,OUTPUT);
  pinMode(testPin, INPUT_PULLUP);
  debouncer.attach(testPin);
  debouncer.interval(DEBOUNCE_TIME);
/*
  show1.addDigit(&(vfd.digit1), 1);
  show1.addDigit(&(vfd.digit2), 2);
  show1.addDigit(&(vfd.digit3), 3);

  show2 = show2builder.add(&(vfd._threezero))
  	->add(&(vfd._s))
  	->add(&(vfd._v))
  	->add(&(vfd._cd))
  	->add(&(vfd._N))
  	->add(&(vfd._p))
  	->add(&(vfd._dvd))
  	->add(&(vfd._pbc))
  	->add(&(vfd._mp3))
	->getScanner();
*/
}      

void loop(){
  debouncer.update();
  assembler.addChar(Serial.read());

  if (debouncer.fell()) {
    lightShowState = !lightShowState;
    //show1.enable(lightShowState);
    //if (lightShowState) vfd._tdvd.setBlink();
    //else vfd._tdvd.setEnabled(false);
  }
 
  if (assembler.isCommandAvailable()) {
    assembler.getCommand(buffer1,COMMANDBUFSIZE);
    controller.obey(buffer1, &vfd);
  }
  
  if (millis() - lasttime2 > ANIMATION_TIME_MS) {
  	vfd.animate();
    	digitalWrite(13,pinState13);
    	pinState13=~pinState13;
  //  	show1.animate();
  //  	if (lightShowState) show2->cycle();
  	lasttime2 = millis();
  }
  
  if (millis()-lasttime1 > CYCLE_TIME_MS) {
  	plexi.cycle();
	lasttime1 = millis();
  }

  

}
