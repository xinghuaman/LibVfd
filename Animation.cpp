#include "Animation.h"

void Animation::begin(String memonic, unsigned long offMask) {
   _memonic = memonic;
   _offMask = offMask;
}

void Animation::addStep(unsigned long mask, unsigned long* bin) {
  _masks[_totalStepsCounter] = mask;
  _bins[_totalStepsCounter] = bin;
  _totalStepsCounter++;
}

void Animation::animate() {
  (*_bins[_animationCounter])|=_offMask;
  (*_bins[_animationCounter])&=~_masks[_animationCounter];
  _animationCounter++;
  if (_animationCounter >= _totalStepsCounter)
    _animationCounter=0;
}
