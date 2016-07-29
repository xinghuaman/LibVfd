#include <AbstractVFD.h>

void AbstractVFD::addFunc(AnimatableFunction* function){
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

AnimatableFunction* AbstractVFD::getFunctionFor(String memonic) {
  for(int i=0;i<_numFunctions;i++){
    if (_functions[i]->getMemonic().equals(memonic))
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
