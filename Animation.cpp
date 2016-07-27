#include "Animation.h"

void Animation::begin(String memonic, unsigned long offMask) {
   AnimatableFunction::begin(memonic);
}

void Animation::addStep(unsigned long mask, unsigned long* bin) {
  _masks[_totalStepsCounter] = mask;
  _bins[_totalStepsCounter] = bin;
  _totalStepsCounter++;
}

void Animation::setEnabled(boolean enabled){
  AnimatableFunction::setEnabled(enabled);
  for(int i=0;i<_totalStepsCounter;i++) {
  	if (enabled) 
	  (*_bins[i])|=_masks[i];
	else 
	  (*_bins[i])&=~_masks[i];
  }
}

void Animation::animate() {
  if (!isBlink()) return;
  (*_bins[_animationCounter])|=_masks[_animationCounter];
  _animationCounter++;
  if (_animationCounter >= _totalStepsCounter)
    _animationCounter=0;
  (*_bins[_animationCounter])&=~_masks[_animationCounter];
}
