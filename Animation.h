#ifndef Animation_h
#define Animation_h

#include <Arduino.h>

class Animation {
   private:
     unsigned long  _masks[10];
     unsigned long* _bins[10];
     unsigned long _offMask;
     byte _totalStepsCounter;
     byte _animationCounter;
     String _memonic;
     
   public:
     void begin(String memonic, unsigned long offMask);
     void addStep(unsigned long mask, unsigned long* bin);
     void animate();
};

#endif
