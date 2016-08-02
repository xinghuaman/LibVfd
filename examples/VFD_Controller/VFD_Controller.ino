#include <TimerOne.h>
#include <Bounce2.h>
#include <AnotherVFD.h>
#include <AbstractVFD.h>
#include <Shifter.h>
#include <AnotherMultiplexer.h>
#include <MirroringBitManipulator.h>
#include <DigitCommandParser.h>
#include <CountingLightShow.h>
#include <LarsonLightShow.h>
#include <LightSwitchCallback.h>

int dataPin = 2;
int latchPin = 3;
int clockPin = 4;
int testPin = 9;


MirroringBitManipulator manipulator;
Shifter shifter;
AnotherVFD anotherVFD;
AnotherMultiplexer plexi(&shifter, anotherVFD.getBins(), 4);
CountingLightShow show1;
LarsonLightShow show2;
Bounce debouncer;

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

  show2.setVfd(&anotherVFD);
  show2.begin();
}      

boolean pinState13=false;
int counter=0;

void timerRoutine(){
  if (counter > 50) {
    anotherVFD.animate();
    digitalWrite(13,pinState13);
    pinState13=~pinState13;
    show1.animate();
    show2.animate();
    counter=0;
  } else {
    counter++;
  }
  plexi.cycle();
}

void nocomprende(String command, String cause) {
  Serial.print("Hein? No comprende! ");
  Serial.print(command);
  Serial.print(" ");
  Serial.println(cause);
}

void loop(){
  debouncer.update();

  if (debouncer.fell()) {
    lightShowState = !lightShowState;
    show1.enable(lightShowState);
    show2.enable(lightShowState);
    if (lightShowState) anotherVFD._tdvd.setBlink();
    else anotherVFD._tdvd.setEnabled(false);
  }
 
  if (Serial.available()>0) {
    String command = Serial.readString();
    DigitCommandParser parser;
    if (!parser.parse(command)) {
      nocomprende(command,"did not parse!");
      return;
    }

    AnimatableFunction* func = anotherVFD.getFunctionFor(parser.getMemonic());
    if (func == NULL) {
      nocomprende(command, "Unknown function!");
       return;
    }

    if (parser.isOn())
       func->setEnabled(true);
    else if (parser.isOff())
       func->setEnabled(false);
    else if (parser.isBlink())
       func->setBlink();
    else if (parser.isNumber()) {
       if (func->getType().equals("SevenSegmentEncoder")) {
         SevenSegmentEncoder* en = (SevenSegmentEncoder*) func;          
         en->encode(parser.getNumber());
       } else {
         nocomprende(command, "It's not a digit!");
       }
    } else {
      nocomprende(command,"Panic!");
    }
  
}

}
