#include "SingleFunction.h"


void SingleFunction::setEnabled(bool enabled) {
  AnimatableFunction::setEnabled(enabled);
  if (enabled) {
    (*_bin)|=_mask;
  } else {
    (*_bin)&=~_mask;
  }
}

void SingleFunction::begin(unsigned long* targetBin, unsigned long mask,
const char* const memonic) {
   AnimatableFunction::begin(memonic);
  _bin=targetBin;
  _mask=mask;
};

void SingleFunction::animate() {
  if (isBlink()) (*_bin)^=_mask;
}
