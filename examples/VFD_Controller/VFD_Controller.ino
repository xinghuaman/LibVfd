
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

#define COMMANDBUFSIZE 50
#define GENERICBUFSIZE 20

const int dataPin = 2;
const int latchPin = 3;
const int clockPin = 4;
const int testPin = 9;
const char global_noparse[] PROGMEM  = "Does not parse!";
const char global_unkfunc[] PROGMEM  = "Unknown Function!";
const char global_sevenseg[] PROGMEM = "SevenSegmentEncoder";
const char global_nodig[] PROGMEM    = "It's not a digit!";
const char global_unknerr[] PROGMEM  = "Unknown Error!";
char buffer[GENERICBUFSIZE];

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
  	funcs[i]->getMemonic(buffer, GENERICBUFSIZE);
  	Serial.print(buffer);
	Serial.print(F(" ("));
	funcs[i]->getType(buffer, GENERICBUFSIZE);
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

    char command[COMMANDBUFSIZE];
    strncpy(command,Serial.readString().c_str(),COMMANDBUFSIZE);
    command[COMMANDBUFSIZE-1] = '\0';

    DigitCommandParser parser;
    if (!parser.parse(command)) {
      strncpy_P(buffer, global_noparse, GENERICBUFSIZE);
      buffer[GENERICBUFSIZE-1] = '\0';
      nocomprende(command, buffer);
      return;
    }

    AnimatableFunction* func = anotherVFD.getFunctionFor(parser.getMemonic());
    if (func == NULL) {
      strncpy_P(buffer, global_unkfunc, GENERICBUFSIZE);
      buffer[GENERICBUFSIZE-1] = '\0';
      nocomprende(command, buffer);
      return;
    }

    if (parser.isOn())
       func->setEnabled(true);
    else if (parser.isOff())
       func->setEnabled(false);
    else if (parser.isBlink())
       func->setBlink();
    else if (parser.isNumber()) {
       func->getType(buffer, GENERICBUFSIZE);
       if (strcmp_P(buffer, global_sevenseg) == 0 ) {
         SevenSegmentEncoder* en = (SevenSegmentEncoder*) func;          
         en->encode(parser.getNumber());
       } else {
         strncpy_P(buffer, global_nodig, GENERICBUFSIZE);
      	 buffer[GENERICBUFSIZE-1] = '\0';
         nocomprende(command, buffer);
       }
    } else {
      strncpy_P(buffer, global_unknerr, GENERICBUFSIZE);
      buffer[GENERICBUFSIZE-1]='\0';
      nocomprende(command,global_unknerr);
    }

    Serial.print(F("Free Memory: "));
    Serial.println(freeMemory());
  
}

}
