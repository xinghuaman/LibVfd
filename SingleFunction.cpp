#include "SingleFunction.h"


void SingleFunction::setEnabled(boolean enabled) {
  AnimatableFunction::setEnabled(enabled);
  if (enabled) {
    (*_bin)|=_mask;
  } else {
    (*_bin)&=~_mask;
  }
}

void SingleFunction::begin(unsigned long* targetBin, unsigned long mask, String memonic) {
   AnimatableFunction::begin(memonic);
  _bin=targetBin;
  _mask=mask;
};

void SingleFunction::animate() {
  if (isBlink()) (*_bin)^=_mask;
}
