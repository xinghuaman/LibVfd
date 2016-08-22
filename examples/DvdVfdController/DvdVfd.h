#ifndef DvdVfd_h
#define DvdVfd_h

#include "AbstractVFD.h"
#include "SevenSegments.h"
#include "Animation.h"
#include "SingleFunction.h"
#include "SevenSegmentEncoder.h"
#include <avr/pgmspace.h>

class DvdVfd : public AbstractVFD {
  public:
    SevenSegments _rightseg;
    SevenSegments _leftseg;
   
    Animation _tdvd;

    SevenSegmentEncoder digit1;
    SevenSegmentEncoder digit2;
    SevenSegmentEncoder digit3;

    SingleFunction _dvdcenter;
    SingleFunction _threezero;
    SingleFunction _backslash;
    SingleFunction _v;
    SingleFunction _cd;
    SingleFunction _p;
    SingleFunction _commas;
    SingleFunction _dash;
    SingleFunction _speakerl;
    SingleFunction _speakerr;
    SingleFunction _s;
    SingleFunction _N;
    SingleFunction _pbc;
    SingleFunction _dvd;
    SingleFunction _mp3;
    SingleFunction _doublepoint;
   
    DvdVfd();
};

#endif
