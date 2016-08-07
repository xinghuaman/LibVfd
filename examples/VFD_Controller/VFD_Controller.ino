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
#include <MemoryFree.h>

const int dataPin = 2;
const int latchPin = 3;
const int clockPin = 4;
const int testPin = 9;
const char global_noparse[] PROGMEM = "Does not parse!";
const char global_unkfunc[] PROGMEM = "Unknown Function!";
const char global_sevenseg[] PROGMEM = "SevenSegmentEncoder";
const char global_nodig[] PROGMEM = "It's not a digit!";
const char global_unknerr[] PROGMEM = "Unknown Error!";
char buffer[30];

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

void nocomprende(const char * const command,const char * const cause) {
  Serial.print(F("Hein? "));
  Serial.print(command);
  Serial.print(F(" "));
  Serial.println(cause);
  Serial.println(F("Valid commands:"));
  AnimatableFunction** funcs = anotherVFD.getFunctions();
  for(int i=0;i<anotherVFD.getNumFunctions();i++) {
  	funcs[i]->getMemonic(buffer);
  	Serial.print(buffer);
	Serial.print(F(" ("));
	funcs[i]->getType(buffer);
	Serial.print(buffer);
	Serial.println(F(")"));
  }
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
    Serial.print(F("Free Memory: "));
    Serial.println(freeMemory());

    String command = Serial.readString();
    DigitCommandParser parser;
    if (!parser.parse(command)) {
      strcpy_P(buffer, global_noparse);
      nocomprende(command.c_str(),buffer);
      return;
    }

    AnimatableFunction* func = anotherVFD.getFunctionFor(parser.getMemonic().c_str());
    if (func == NULL) {
      strcpy_P(buffer, global_unkfunc);
      nocomprende(command.c_str(), buffer);
      return;
    }

    if (parser.isOn())
       func->setEnabled(true);
    else if (parser.isOff())
       func->setEnabled(false);
    else if (parser.isBlink())
       func->setBlink();
    else if (parser.isNumber()) {
       func->getType(buffer);
       if (strcmp_P(buffer, global_sevenseg) == 0 ) {
         SevenSegmentEncoder* en = (SevenSegmentEncoder*) func;          
         en->encode(parser.getNumber());
       } else {
         strcpy_P(buffer, global_nodig);
         nocomprende(command.c_str(), buffer);
       }
    } else {
      strcpy_P(buffer, global_unknerr);
      nocomprende(command.c_str(),global_unknerr);
    }

    Serial.print(F("Free Memory: "));
    Serial.println(freeMemory());
  
}

}
