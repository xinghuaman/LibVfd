#ifndef LarsonLightShowBuilder_h
#define LarsonLightShowBuilder_h

#include <AnimatableLightSwitchCallback.h>
#include <SingleFunction.h>
#include <LarsonScanner.h>

class LarsonLightShowBuilder {
  private:
	AnimatableLightSwitchCallback _callback;
	LarsonScanner _scanner;


  public:
    LarsonLightShowBuilder* add(SingleFunction* function);
    void finish();
    LarsonScanner*  getScanner();
};

#endif
