#ifndef SevenSegmentEncoder_h
#define SevenSegmentEncoder_h

#include "SevenSegments.h"

class SevenSegmentEncoder {
  private:
    SevenSegments* _mySegments[5];
    unsigned long* _myBins[5];

    byte _numSegments;
    byte _radix;
  
  public:
    void begin(byte radix);
    void addSegment(SevenSegments* segment, unsigned long* bin);
    void encode(int number);
};
#endif
