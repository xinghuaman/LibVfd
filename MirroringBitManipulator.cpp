#include "MirroringBitManipulator.h"


void MirroringBitManipulator::setMirroring(unsigned long startMask, int numBits) {
	_startMask=startMask;
	_numBits=numBits;
}

unsigned long MirroringBitManipulator::manipulate(unsigned long bits){
	unsigned long mirrored=0;
  	for (int i=0;i<_numBits;i++) {
   
    		if ((bits & _startMask) > 0) 
      			mirrored|=_startMask;
    		bits>>=1;
    		if ((i+1)<_numBits) mirrored<<=1;
  	}
	return mirrored;
}
