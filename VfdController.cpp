#include <VfdController.h>
#include <MemoryFree.h>
#include <SevenSegmentEncoder.h>
#include <EqualsLikeCommandParser.h>

#include <string.h>
#include <avr/pgmspace.h>

#include <Arduino.h>

VfdController* VfdController::add2Show(SingleFunction* singleFunction) {
	//_builder.add(singleFunction);
	return this;
}

void VfdController::begin(AbstractVFD* vfd) {
	_vfd = vfd;
	//_builder.finish();
	
	AnimatableFunction** funcs = _vfd->getFunctions();

	for(int i=0; i < _vfd->getNumFunctions(); i++) {
		Serial.print(F("Testing: "));
		Serial.println(i);

		AnimatableFunction* func = funcs[i];

		if (func->getRawType() == 1) {
			Serial.println(F("Adding"));
			//_show.addDigit((SevenSegmentEncoder*) funcs[i], i);
		}
		
	}
}

void VfdController::animate() {
	if (!_isLightShowEnabled) return;
	//_builder.getScanner()->cycle();	
//	_show.animate();
}

void VfdController::enableLightShow(bool enabled) {
	_isLightShowEnabled = enabled;
	//_show.enable(_isLightShowEnabled);
}


#define VFDCONTROLLER_BUFFSIZE 20

void VfdController::nocomprende(const char * const command,const char * const cause) {
  char vfdcontroller_buffer[VFDCONTROLLER_BUFFSIZE];

  Serial.print(F("What? "));
  Serial.print(command);
  Serial.print(F(" -->"));
  strncpy_P(vfdcontroller_buffer, cause, VFDCONTROLLER_BUFFSIZE);
  vfdcontroller_buffer[VFDCONTROLLER_BUFFSIZE-1] = '\0';
  Serial.print(vfdcontroller_buffer);
  Serial.println(F("<--\nValid commands:"));
  AnimatableFunction** funcs = _vfd->getFunctions();
  for(int i=0;i<_vfd->getNumFunctions();i++) {
  	funcs[i]->getMemonic(vfdcontroller_buffer,VFDCONTROLLER_BUFFSIZE );
  	Serial.println(vfdcontroller_buffer);
  }
  Serial.print(F("Free Memory: "));
  Serial.println(freeMemory());
}

void VfdController::obey(char command[]){
 
    Serial.print(F("Free Memory: "));
    Serial.println(freeMemory());

    EqualsLikeCommandParser parser;
    EqualsLikeToken token;

    if (parser.parse(command, &token)!=0) {
      nocomprende(command, PSTR("Does not parse!"));
      return;
    }

    AnimatableFunction* func = _vfd->getFunctionFor(token.subject);
    if (func == NULL) {
      nocomprende(command, PSTR("Unknown Function"));
      return;
    }

    if (strcmp_P(token.object, PSTR("on"))==0)
       func->setEnabled(true);
    else if (strcmp_P(token.object, PSTR("off"))==0)
       func->setEnabled(false);
    else if (strcmp_P(token.object, PSTR("blink"))==0)
       func->setBlink();
    else {
       if (func->getRawType() == 1) {
       	 long number = strtol(token.object,NULL,10);
	 Serial.print(F("Got Number: "));
	 Serial.println(number);
         SevenSegmentEncoder* en = (SevenSegmentEncoder*) func;          
         en->encode(number);
       } else {
         nocomprende(command, PSTR("That is no digit!"));
       }
    } 
}

