#ifndef Animation_h
#define Animation_h

#include "AnimatableFunction.h"

class Animation : public AnimatableFunction {
   private:
     unsigned long  _masks[10];
     unsigned long* _bins[10];
     unsigned long _offMask;
     unsigned char _totalStepsCounter;
     unsigned char _animationCounter;
     
   public:
     virtual void begin(const char* const memonic, unsigned long offMask);
     virtual void setEnabled(bool enabled);
     virtual void addStep(unsigned long mask, unsigned long* bin);
     virtual void animate();
};

#endif
