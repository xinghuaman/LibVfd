#ifndef AnotherVFD_h
#define AnotherVFD_h

#include "SevenSegments.h"
#include "SevenSegmentEncoder.h"
#include "DigitCommandParser.h"

#include "Animation.h"
#include "SingleFunction.h"
#include "SingleFunctionCommandParser.h"

class AnotherVFD {
  private:
    unsigned long _bins[4];
    
    SevenSegments _rightseg;
    SevenSegments _leftseg;
    SevenSegmentEncoder _encoder[3];
   
    Animation _tdvd;
    
    SingleFunction _singlefunctions[20];
    int _numSingleFunctions=0;
    
    byte dvdAnimationCounter=0;
    
    void addSingleFunction(int bin, unsigned long mask, String memonic);
    
  
   
  public:
    AnotherVFD();
    unsigned long* getBins();
    void animate();
    AnimatableFunction* getFunctionFor(String memonic);
};

#endif
