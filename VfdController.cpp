#include <VfdController.h>
#include <MemoryFree.h>
#include <SevenSegmentEncoder.h>

char VfdController::buffer[GENERICBUFSIZE];

void VfdController::nocomprende(const char * const command,const char * const cause, AbstractVFD* vfd) {
  Serial.print(F("Hein? "));
  Serial.print(command);
  Serial.print(F(" "));
  strncpy_P(buffer, cause, GENERICBUFSIZE);
  buffer[GENERICBUFSIZE-1] = '\0';
  Serial.println(cause);
  Serial.println(F("Valid commands:"));
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

    DigitCommandParser parser;
    if (!parser.parse(command)) {
      nocomprende(command, global_noparse, vfd);
      return;
    }

    AnimatableFunction* func = vfd->getFunctionFor(parser.getMemonic());
    if (func == NULL) {
      nocomprende(command, global_unkfunc, vfd);
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
         nocomprende(command, global_nodig, vfd);
       }
    } else {
      nocomprende(command,global_unknerr, vfd);
    }
}

