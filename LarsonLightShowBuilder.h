#ifndef LarsonLightShowBuilder_h
#define CoutingLightShowBuilder_h

#include <AnimatableLightSwitchCallback.h>
#include <SingleFunction.h>
#include <LarsonSequenceGenerator.h>
#include <LightSequencer.h>

class LarsonLightShowBuilder {
  private:
	AnimatableLightSwitchCallback _callback;
	int _sequence[150];
	LightSequencer _sequencer;


  public:
    LarsonLightShowBuilder* add(SingleFunction* function);
    LightSequencer*  getSequencer();
};

#endif
