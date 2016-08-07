#include "AnimatableFunction.h"
#include <avr/pgmspace.h>

void AnimatableFunction::setEnabled(bool enabled) {
  _blink=false;
}

void AnimatableFunction::setBlink() {
  _blink=true;
}

void AnimatableFunction::begin(const char* const memonic) {
  _memonic=(char *) memonic;
};

void AnimatableFunction::getMemonic(char* buffer, int bufsize) {
  strncpy_P(buffer,_memonic, bufsize);
  buffer[bufsize-1] = '\0';
}

bool AnimatableFunction::isBlink() {
  return _blink;
}

void AnimatableFunction::getType(char* buffer, int bufsize) {
   strncpy_P(buffer, txt_AnimatableFunction, bufsize);
   buffer[bufsize-1] = '\0';
}
