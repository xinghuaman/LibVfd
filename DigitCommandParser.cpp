#include "DigitCommandParser.h"
#include "SevenSegmentEncoder.h"

void DigitCommandParser::begin(String memonic, SevenSegmentEncoder *encoder) {
  _memonic = memonic;
  _encoder = encoder;
}

boolean DigitCommandParser::tryObey(String command) {
  if (command.substring(0,_memonic.length()).equals(_memonic)) {
     Serial.print("Command: ");
     Serial.println(command);
     String numberPart = command.substring(_memonic.length()+1,command.length()-1);
     Serial.print("Numberpart: ");
     Serial.println(numberPart);
     if (numberPart.equals("off")) {
       
     } else {
       int number = strtoul(numberPart.c_str(),NULL,10);
       Serial.println(number);
       Serial.println((unsigned long)_encoder,HEX);
       _encoder->encode(number);
    }
    return true;
  }
  return false;
  
};

String DigitCommandParser::getMemonic() {
  return _memonic;
}
