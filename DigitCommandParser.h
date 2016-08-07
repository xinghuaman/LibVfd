#ifndef DigitCommandParser_h
#define DigitCommandParser_h


class DigitCommandParser {
  private:
    char* _memonic;
    bool _isOff;
    bool _isNumber;
    bool _isBlink;
    bool _isOn;
    int _number;
  
  public:
    DigitCommandParser();
    bool parse(char[]);
    char* getMemonic();
    bool isOff();
    bool isNumber();
    bool isBlink();
    bool isOn();
    int getNumber();
};

#endif
