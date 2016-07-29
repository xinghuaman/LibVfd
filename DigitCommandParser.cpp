#include "DigitCommandParser.h"

DigitCommandParser::DigitCommandParser() {
 }

boolean DigitCommandParser::parse(String command) {
 _isOff=false;
 _isOn=false;
 _isBlink=false;
 _number=0;
 _isNumber=false;

  command.trim();
  int index = command.indexOf('=');
  if (index < 1) return false;
  if (index>=command.length()-1) return false;
  _memonic = command.substring(0,index);
  String instruction = command.substring(index+1);
  Serial.print("Command: ");
  Serial.println(command);
  Serial.print("Memonic: ");
  Serial.println(_memonic);
  Serial.print("Numberpart: ");
  Serial.println(instruction);
  if (instruction.equals("off")) {
    Serial.println("Setting off!");
    _isOff=true;  
  } else if (instruction.equals("on")) {
    Serial.println("Setting on!");
    _isOn=true;
  } else if (instruction.equals("blink")) {
    Serial.println("Setting blink!");
    _isBlink=true;
  } else {
   _number = strtoul(instruction.c_str(),NULL,10);
    Serial.println(_number);
   _isNumber=true;
  }
  return true;
};

String DigitCommandParser::getMemonic() {
  return _memonic;
}

boolean DigitCommandParser::isOff() {
  return _isOff;
}

boolean DigitCommandParser::isOn() {
  return _isOn;
}

boolean DigitCommandParser::isNumber() {
  return _isNumber;
}

boolean DigitCommandParser::isBlink() {
  return _isBlink;
}

int DigitCommandParser::getNumber() {
  return _number;
}
