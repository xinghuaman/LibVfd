#include "CountingLightShow.h"

CountingLightShow::CountingLightShow() {
  _numDigits=0;
}

void CountingLightShow::addDigit(SevenSegmentEncoder* encoder, int
	initialCount) {
	if (_numDigits >= COUNTINGLIGHTSHOW_MAXDIGITS-1) return;
	_digits[_numDigits] = encoder;
	_counters[_numDigits] = initialCount;
	_numDigits++;
}

void CountingLightShow::enable(boolean enabled) {
	_enabled = enabled;
	for(int i=0;i<_numDigits;i++) {
		_digits[i]->setEnabled(enabled);
	}
}

void CountingLightShow::animate() {
	if (!_enabled) return;

	for(int i=0;i<_numDigits;i++) {
		_digits[i]->encode(_counters[i]);
		_counters[i]++;
	}
}


