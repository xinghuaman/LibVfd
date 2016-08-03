#include "AnimatableFunction.h"


void AnimatableFunction::setEnabled(boolean enabled) {
  _blink=false;
}

void AnimatableFunction::setBlink() {
  _blink=true;
}

void AnimatableFunction::begin(String memonic) {
  _memonic=memonic;
};

String AnimatableFunction::getMemonic() {
  Serial.print("getMemonic(): ");
  Serial.println(_memonic);
  return _memonic;
}

boolean AnimatableFunction::isBlink() {
  return _blink;
}

String AnimatableFunction::getType() {
  return "AnimatableFunction";
}
