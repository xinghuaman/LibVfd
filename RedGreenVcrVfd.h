#ifndef RedGreenVcrVfd_h
#define RedGreenVcrVfd_h

#include "AbstractVFD.h"
#include "SevenSegments.h"
#include "Animation.h"
#include "SingleFunction.h"
#include "SevenSegmentEncoder.h"


class RedGreenVcrVfd : public AbstractVFD {
  public:
    SevenSegments _mostused;
   
    SevenSegmentEncoder digit1;
    SevenSegmentEncoder digit2;
    SevenSegmentEncoder digit3;

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
    SingleFunction _rec;
    SingleFunction _pse;
    SingleFunction _ff;
    SingleFunction _rwd;


    RedGreenVcrVfd();
};

#endif
