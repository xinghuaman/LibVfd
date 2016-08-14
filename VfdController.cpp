#include <VfdController.h>
#include <MemoryFree.h>
#include <SevenSegmentEncoder.h>
#include <EqualsLikeCommandParser.h>

#include <string.h>
#include <avr/pgmspace.h>

char VfdController::buffer[GENERICBUFSIZE];

void VfdController::nocomprende(const char * const command,const char * const cause, AbstractVFD* vfd) {
  Serial.print(F("What? "));
  Serial.print(command);
  Serial.print(F(" -->"));
  strncpy_P(buffer, cause, GENERICBUFSIZE);
  buffer[GENERICBUFSIZE-1] = '\0';
  Serial.print(buffer);
  Serial.println(F("<--\nValid commands:"));
  AnimatableFunction** funcs = vfd->getFunctions();
  for(int i=0;i<vfd->getNumFunctions();i++) {
  	funcs[i]->getMemonic(buffer, GENERICBUFSIZE);
  	Serial.print(buffer);
	Serial.print(F(" ("));
	funcs[i]->getType(buffer, GENERICBUFSIZE);
	Serial.print(buffer);
	Serial.println(F(")"));
  }
}


void VfdController::obey(char command[], AbstractVFD* vfd){
 
    Serial.print(F("Free Memory: "));
    Serial.println(freeMemory());

    EqualsLikeCommandParser parser;
    EqualsLikeToken token;

    if (parser.parse(command, &token)!=0) {
      nocomprende(command, PSTR("Does not parse!"), vfd);
      return;
    }

    AnimatableFunction* func = vfd->getFunctionFor(token.subject);
    if (func == NULL) {
      nocomprende(command, PSTR("Unknown Function"), vfd);
      return;
    }

    if (strcmp_P(token.object, PSTR("on"))==0)
       func->setEnabled(true);
    else if (strcmp_P(token.object, PSTR("off"))==0)
       func->setEnabled(false);
    else if (strcmp_P(token.object, PSTR("blink"))==0)
       func->setBlink();
    else {
       func->getType(buffer, GENERICBUFSIZE);
       if (strcmp_P(buffer, PSTR("SevenSegmentEncoder")) == 0 ) {
       	 long number = strtol(token.object,NULL,10);
         SevenSegmentEncoder* en = (SevenSegmentEncoder*) func;          
         en->encode(number);
       } else {
         nocomprende(command, PSTR("That is no digit!"), vfd);
       }
    } 
}

