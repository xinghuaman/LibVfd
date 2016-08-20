#ifndef RedGreenVcrVfd_h
#define RedGreenVcrVfd_h

#include "AbstractVFD.h"
#include "SevenSegments.h"
#include "Animation.h"
#include "SingleFunction.h"
#include "SevenSegmentEncoder.h"

#define GENERICBUFFIZE 50

class RedGreenVcrVfd : public AbstractVFD {
  public:
    SevenSegments _mostused;
    SevenSegments _outsider;
   
    SevenSegmentEncoder digit1;
    SevenSegmentEncoder digit2;
    SevenSegmentEncoder digit3;
    SevenSegmentEncoder digit4;
    SevenSegmentEncoder digit5;
    SevenSegmentEncoder digit6;

    SingleFunction _dp;
    SingleFunction _ovrflw1;

    SingleFunction _pwr;
    SingleFunction _cas;
    SingleFunction _vcr;
    SingleFunction _bs;
    SingleFunction _clk;
    SingleFunction _otr;
    SingleFunction _wkly;
    SingleFunction _su;
    SingleFunction _mo;
    SingleFunction _tu;
    SingleFunction _we;
    SingleFunction _th;
    SingleFunction _fr;
    SingleFunction _sa;

    SingleFunction _line;
    SingleFunction _dual;
    SingleFunction _on;
    SingleFunction _ch;
    SingleFunction _st;
    SingleFunction _off;
    SingleFunction _catv;
    SingleFunction _sap;
    SingleFunction _am;
    SingleFunction _aft;
    SingleFunction _hifi;
    SingleFunction _pm;
    SingleFunction _err;

    SingleFunction _ply;
    SingleFunction _pply;
    SingleFunction _fply;
    SingleFunction _rec;
    SingleFunction _pse;
    SingleFunction _ppse;
    SingleFunction _ff;
    SingleFunction _rwd;

    SingleFunction _rep;
    SingleFunction _s;
    SingleFunction _l;
    SingleFunction _p;
    SingleFunction _index;
    SingleFunction _dew;
    SingleFunction _vps;
    SingleFunction _pgm;
    SingleFunction _1;
    SingleFunction _2;
    SingleFunction _3;
    SingleFunction _4;
    SingleFunction _5;
    SingleFunction _6;
    SingleFunction _7;
    SingleFunction _8;

    SingleFunction _m;
    SingleFunction _h;
    SingleFunction _sek;

    SingleFunction _ldash;
    SingleFunction _udash;
    RedGreenVcrVfd();
};

#endif
