#include <TimerOne.h>
#include <Bounce2.h>
#include <AnotherVFD.h>
#include <Shifter.h>
#include <AnotherMultiplexer.h>
#include <MirroringBitManipulator.h>
#include <DigitCommandParser.h>

int dataPin = 2;
int latchPin = 3;
int clockPin = 4;


MirroringBitManipulator manipulator;
Shifter shifter;
AnotherVFD anotherVFD;
AnotherMultiplexer plexi(&shifter, anotherVFD.getBins(), 4);


void setup() {
  
  Serial.begin(9600);
  Timer1.initialize(2000);
  Timer1.attachInterrupt(timerRoutine);
  manipulator.setMirroring(0x01,20);
  shifter.begin(2,3,4,&manipulator);
  pinMode(13,OUTPUT);
}      

boolean pinState13=false;
int counter=0;

void timerRoutine(){
  if (counter > 50) {
    anotherVFD.animate();
    digitalWrite(13,pinState13);
    pinState13=~pinState13;
    counter=0;
  } else {
    counter++;
  }
  plexi.cycle();
}

void nocomprende(String command, String cause) {
  Serial.print("No comprende: ");
  Serial.print(command);
  Serial.print(" ");
  Serial.println(cause);
}

void loop(){
 
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
