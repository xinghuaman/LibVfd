
#include <TimerOne.h>
#include <Bounce2.h>
#include "AnotherVFD.h"
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


#define COMMANDBUFSIZE 50

const int dataPin = 2;
const int latchPin = 3;
const int clockPin = 4;
const int testPin = 9;

MirroringBitManipulator manipulator;
Shifter shifter;
AnotherVFD anotherVFD;
AnotherMultiplexer plexi(&shifter, anotherVFD.getBins(), 4);
CountingLightShow show1;
LarsonScanner* show2;
LarsonLightShowBuilder show2builder;
Bounce debouncer;
VfdController controller;

boolean lightShowState=false;

void setup() {
  
  Serial.begin(9600);
  Timer1.initialize(2000);
  Timer1.attachInterrupt(timerRoutine);
  manipulator.setMirroring(0x01,20);
  shifter.begin(2,3,4,&manipulator);
  pinMode(13,OUTPUT);
  pinMode(testPin, INPUT_PULLUP);
  debouncer.attach(testPin);
  debouncer.interval(500);
  show1.addDigit(&(anotherVFD.digit1), 1);
  show1.addDigit(&(anotherVFD.digit2), 2);
  show1.addDigit(&(anotherVFD.digit3), 3);

  show2 = show2builder.add(&(anotherVFD._threezero))
  	->add(&(anotherVFD._s))
  	->add(&(anotherVFD._v))
  	->add(&(anotherVFD._cd))
  	->add(&(anotherVFD._N))
  	->add(&(anotherVFD._p))
  	->add(&(anotherVFD._dvd))
  	->add(&(anotherVFD._pbc))
  	->add(&(anotherVFD._mp3))
	->getScanner();
}      

boolean pinState13=false;
int counter=0;

void timerRoutine(){
  if (counter > 50) {
    anotherVFD.animate();
    digitalWrite(13,pinState13);
    pinState13=~pinState13;
    show1.animate();
    if (lightShowState) show2->cycle();
    counter=0;
  } else {
    counter++;
  }
  plexi.cycle();
}


void loop(){
  debouncer.update();

  if (debouncer.fell()) {
    lightShowState = !lightShowState;
    show1.enable(lightShowState);
    if (lightShowState) anotherVFD._tdvd.setBlink();
    else anotherVFD._tdvd.setEnabled(false);
  }
 
  if (Serial.available()>0) {
    char command[COMMANDBUFSIZE];
    strncpy(command,Serial.readString().c_str(),COMMANDBUFSIZE);
    command[COMMANDBUFSIZE-1] = '\0';

    controller.obey(command, &anotherVFD);
  }

}
