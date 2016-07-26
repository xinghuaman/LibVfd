#ifndef MirroringBitManipulator_h
#define MirroringBitManipulator_h

#include "BitManipulator.h"

class MirroringBitManipulator : public BitManipulator{
	private:
		int _numBits;
		int _startMask;

	public:
		void setMirroring(unsigned long startMask, int numBits);
		unsigned long manipulate(unsigned long bits);
};

#endif
