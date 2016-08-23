#include "LarsonLightShowBuilder.h"

LarsonLightShowBuilder* LarsonLightShowBuilder::add(SingleFunction* func) {
	_callback.addFunction(func);
	return this;
}

LightSequencer* LarsonLightShowBuilder::getSequencer() {
	LarsonSequenceGenerator generator;
	generator.begin(_callback.getNumFunctions(),0, 3, _sequence, _sequenceLength);
	_sequencer.begin(&_callback,_sequence);
	return &_sequencer;
}
