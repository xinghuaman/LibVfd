#include <AbstractVFD.h>
#include <string.h>
#include <avr/pgmspace.h>

void AbstractVFD::addFunc(AnimatableFunction* function){
  if (_numFunctions >= ABSTRACTVFD_MAXFUNCTIONS - 1) return;
  _functions[_numFunctions++] = function;
}

AbstractVFD::AbstractVFD()
{
  _numFunctions=0;
  _numbins=0;
};

void AbstractVFD::animate(){
  for(int i=0;i<_numFunctions;i++){
    _functions[i]->animate();
  }
};

AnimatableFunction* AbstractVFD::getFunctionFor(const char * const memonic) {
  char buffer[ABSTRACTVFD_COMPAIRBUFFSIZE];
  for(int i=0;i<_numFunctions;i++){
    _functions[i]->getMemonic(buffer, ABSTRACTVFD_COMPAIRBUFFSIZE);
    buffer[ABSTRACTVFD_COMPAIRBUFFSIZE-1] = '\0';
    //Serial.println(buffer);
    if (strcmp(buffer, memonic) == 0)
      return _functions[i];
  }
  return NULL;
}

int AbstractVFD::getNumFunctions() {
  return _numFunctions;
}

AnimatableFunction** AbstractVFD::getFunctions() {
  return _functions;
}

int AbstractVFD::getNumBins(){
  return _numbins;
}

unsigned long* AbstractVFD::getBins() {
  return _bins;
}
