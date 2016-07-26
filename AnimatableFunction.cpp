#include "AnimatableFunction.h"


void AnimatableFunction::setEnabled(boolean enabled) {
  _blink = false;
}

void AnimatableFunction::setBlink() {
  _blink=true;
}

void AnimatableFunction::begin(String memonic) {
  _memonic=memonic;
};

String AnimatableFunction::getMemonic() {
  return _memonic;
}

boolean AnimatableFunction::isBlink() {
  return _blink;
}
