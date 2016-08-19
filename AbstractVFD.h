#ifndef AbstractVFD_h
#define AbstractVFD_h

#include "AnimatableFunction.h"

class AbstractVFD {
  protected:
    int _numbins;
    unsigned long _bins[10];
    
    AnimatableFunction* _functions[70];
    int _numFunctions;
   
    void addFunc(AnimatableFunction* function);
   
  public:
    AbstractVFD();
    int getNumBins();
    unsigned long* getBins();

    virtual void animate();

    AnimatableFunction* getFunctionFor(const char* const memonic);
    
    int getNumFunctions();
    AnimatableFunction** getFunctions();

};

#endif
