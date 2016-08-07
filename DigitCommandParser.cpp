#include "DigitCommandParser.h"
#include <string.h>

#include <Arduino.h>

DigitCommandParser::DigitCommandParser() {
 }

bool DigitCommandParser::parse(char command[]) {
 _isOff=false;
 _isOn=false;
 _isBlink=false;
 _number=0;
 _isNumber=false;

  char* saveptr;
 

  _memonic = strtok_r(command,"=", &saveptr);
  if (_memonic == NULL) return false;

  char* instruction = strtok_r(NULL,"=", &saveptr);
  if (instruction == NULL) return false;

  Serial.print("Command: ");
  Serial.println(command);
  Serial.print("Memonic: ");
  Serial.println(_memonic);
  Serial.print("Numberpart: ");
  Serial.println(instruction);
  if (!strncmp(instruction,"off",3)) {
    Serial.println("Setting off!");
    _isOff=true;  
  } else if (!strncmp(instruction, "on",2)) {
    Serial.println("Setting on!");
    _isOn=true;
  } else if (!strncmp(instruction,"blink",2)) {
    Serial.println("Setting blink!");
    _isBlink=true;
  } else {
   _number = strtoul(instruction,NULL,10);
    Serial.println(_number);
   _isNumber=true;
  }
  return true;
};

char* DigitCommandParser::getMemonic() {
  return _memonic;
}

bool DigitCommandParser::isOff() {
  return _isOff;
}

bool DigitCommandParser::isOn() {
  return _isOn;
}

bool DigitCommandParser::isNumber() {
  return _isNumber;
}

bool DigitCommandParser::isBlink() {
  return _isBlink;
}

int DigitCommandParser::getNumber() {
  return _number;
}
