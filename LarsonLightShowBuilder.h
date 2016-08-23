#ifndef LarsonLightShowBuilder_h
#define CoutingLightShowBuilder_h

#include <AnimatableLightSwitchCallback.h>
#include <SingleFunction.h>
#include <LarsonSequenceGenerator.h>
#include <LightSequencer.h>

#define LarsonLightShowBuilderSEQLEN 150

class LarsonLightShowBuilder {
  private:
	AnimatableLightSwitchCallback _callback;
	int _sequence[LarsonLightShowBuilderSEQLEN];
	const int _sequenceLength = LarsonLightShowBuilderSEQLEN;
	LightSequencer _sequencer;


  public:
    LarsonLightShowBuilder* add(SingleFunction* function);
    LightSequencer*  getSequencer();
};

#endif
