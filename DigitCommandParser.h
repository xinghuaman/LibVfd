#ifndef DigitCommandParser_h
#define DigitCommandParser_h

#include "SevenSegmentEncoder.h"

class DigitCommandParser {
  private:
    String _memonic;
    SevenSegmentEncoder* _encoder;
  
  public:
    void begin(String memonic, SevenSegmentEncoder* encoder);
    boolean tryObey(String command);
    String getMemonic();
};

#endif
