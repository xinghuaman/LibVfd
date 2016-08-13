#include "LarsonLightShowBuilder.h"

LarsonLightShowBuilder* LarsonLightShowBuilder::add(SingleFunction* func) {
	_callback.addFunction(func);
	return this;
}

LarsonScanner* LarsonLightShowBuilder::getScanner() {
	_scanner.begin(_callback.getNumFunctions(), 0, 3, &_callback);
	return &_scanner;
}
