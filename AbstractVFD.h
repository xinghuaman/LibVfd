#ifndef AbstractVFD_h
#define AbstractVFD_h

#define ABSTRACTVFD_MAXFUNCTIONS 10 
#define ABSTRACTVFD_COMPAIRBUFFSIZE 20
#define ABSTRACTVFD_MAXBINS 10

#include "AnimatableFunction.h"

class AbstractVFD {
  protected:
    int _numbins;
    unsigned long _bins[ABSTRACTVFD_MAXBINS];
    
    AnimatableFunction* _functions[ABSTRACTVFD_MAXFUNCTIONS];
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
