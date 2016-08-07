#include <InvertingBitManipulator.h>

void InvertingBitManipulator::begin(unsigned long invMask) {
	_invMask = invMask;
}

unsigned long InvertingBitManipulator::manipulate(unsigned long bits) {
	return bits ^ _invMask;
}
