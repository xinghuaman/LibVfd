#ifndef LarsonLightShowBuilder_h
#define CoutingLightShowBuilder_h

#include <AnimatableLightSwitchCallback.h>
#include <SingleFunction.h>
#include <LarsonScanner.h>

class LarsonLightShowBuilder {
  private:
  	LarsonScanner _scanner;
	AnimatableLightSwitchCallback _callback;

  public:
    LarsonLightShowBuilder* add(SingleFunction* function);
    LarsonScanner* getScanner();
};

#endif
