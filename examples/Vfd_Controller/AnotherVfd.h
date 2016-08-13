#ifndef AnotherVfd_h
#define AnotherVfd_h

#include "AbstractVFD.h"
#include "SevenSegments.h"
#include "Animation.h"
#include "SingleFunction.h"
#include "SevenSegmentEncoder.h"
#include <avr/pgmspace.h>

const char global_digit1[] PROGMEM = "digit1";
const char global_digit2[] PROGMEM = "digit2";
const char global_digit3[] PROGMEM = "digit3";
const char global_ani[] PROGMEM = "ani";
const char global_dvdcenter[] PROGMEM = "dvdcenter";
const char global_threezero[] PROGMEM = "threezero";
const char global_backslash[] PROGMEM = "blackslash";
const char global_v[] PROGMEM = "v";
const char global_cd[] PROGMEM = "cd";
const char global_p[] PROGMEM = "p";
const char global_commas[] PROGMEM = "commas";
const char global_dash[] PROGMEM = "dash";
const char global_spl[] PROGMEM = "spl";
const char global_spr[] PROGMEM = "spr";
const char global_s[] PROGMEM = "s";
const char global_n[] PROGMEM = "n";
const char global_pbc[] PROGMEM = "pbc";
const char global_dvd[] PROGMEM = "dvd";
const char global_mp3[] PROGMEM = "mp3";
const char global_dp[] PROGMEM = "dp";


class AnotherVfd : public AbstractVFD {
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
   
    AnotherVfd();
};

#endif
