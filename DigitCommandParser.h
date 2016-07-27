#ifndef DigitCommandParser_h
#define DigitCommandParser_h

#include <Arduino.h>

class DigitCommandParser {
  private:
    String _memonic;
    boolean _isOff;
    boolean _isNumber;
    boolean _isBlink;
    boolean _isOn;
    int _number;
  
  public:
    DigitCommandParser();
    boolean parse(String command);
    String getMemonic();
    boolean isOff();
    boolean isNumber();
    boolean isBlink();
    boolean isOn();
    int getNumber();
};

#endif
