#include "LarsonLightShowBuilder.h"

LarsonLightShowBuilder* LarsonLightShowBuilder::add(SingleFunction* func) {
	_callback.addFunction(func);
	return this;
}

void LarsonLightShowBuilder::finish() {
	_scanner.begin(_callback.getNumFunctions(),0, 3, &_callback);
	
}

LarsonScanner* LarsonLightShowBuilder::getScanner() {
	return &_scanner;
}
