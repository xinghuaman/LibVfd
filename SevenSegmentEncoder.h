#ifndef SevenSegmentEncoder_h
#define SevenSegmentEncoder_h

#include "SevenSegments.h"
#include "AnimatableFunction.h"

#include <avr/pgmspace.h>

const char txt_SevenSegmentEncoder[] PROGMEM = "SevenSegmentEncoder";

class SevenSegmentEncoder : public AnimatableFunction {
  private:
    SevenSegments* _mySegments[5];
    unsigned long* _myBins[5];

    byte _numSegments;
    byte _radix;

    AnimatableFunction* _overflow;
    AnimatableFunction* _minus;
  
  public:
    virtual void getType(char* buffer, int bufsize);
    virtual void begin(byte radix, const char* const memonic);
    virtual void addSegment(SevenSegments* segment, unsigned long* bin);
    virtual void encode(int number);
    virtual void setEnabled(boolean enabled);
    virtual void setOverflow(AnimatableFunction* overflow);
    virtual void setMinus(AnimatableFunction* minus);
    virtual void animate();
};
#endif
