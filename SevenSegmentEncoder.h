#ifndef SevenSegmentEncoder_h
#define SevenSegmentEncoder_h

#include "SevenSegments.h"
#include "AnimatableFunction.h"

class SevenSegmentEncoder : public AnimatableFunction {
  private:
    SevenSegments* _mySegments[5];
    unsigned long* _myBins[5];

    byte _numSegments;
    byte _radix;
  
  public:
    virtual String getType();
    virtual void begin(byte radix, String memonic);
    virtual void addSegment(SevenSegments* segment, unsigned long* bin);
    virtual void encode(int number);
    virtual void setEnabled(boolean enabled);
    virtual void animate();
};
#endif
