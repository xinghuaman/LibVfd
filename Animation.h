#ifndef Animation_h
#define Animation_h

#include "AnimatableFunction.h"
#include <Arduino.h>

class Animation : public AnimatableFunction {
   private:
     unsigned long  _masks[10];
     unsigned long* _bins[10];
     unsigned long _offMask;
     byte _totalStepsCounter;
     byte _animationCounter;
     
   public:
     virtual void begin(String memonic, unsigned long offMask);
     virtual void setEnabled(boolean enabled);
     virtual void addStep(unsigned long mask, unsigned long* bin);
     virtual void animate();
};

#endif
