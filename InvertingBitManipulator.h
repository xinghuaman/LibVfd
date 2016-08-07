#ifndef InvertingBitManipulator_h
#define InvertingBitManipulator_h

#include <BitManipulator.h>

class InvertingBitManipulator : public BitManipulator {
	private:
		unsigned long _invMask;

	public:
		void begin(unsigned long invMask);	
		virtual unsigned long manipulate(unsigned long bits);
};

#endif
