#ifndef RedGreenVcrVfd_h
#define RedGreenVcrVfd_h

#include "AbstractVFD.h"
#include "SevenSegments.h"
#include "Animation.h"
#include "SingleFunction.h"
#include "SevenSegmentEncoder.h"

#define GENERICBUFFIZE 50

const char RGV_digit1[] PROGMEM = "digit1";
const char RGV_digit2[] PROGMEM = "digit2";
const char RGV_digit3[] PROGMEM = "digit3";
const char RGV_digit4[] PROGMEM = "digit4";
const char RGV_digit5[] PROGMEM = "digit5";
const char RGV_digit6[] PROGMEM = "digit6";

const char RGV_dp[] PROGMEM = ":";

const char RGV_pwr[] PROGMEM = "pwr";
const char RGV_cas[] PROGMEM = "cas";
const char RGV_vcr[] PROGMEM = "vcr";
const char RGV_bs[] PROGMEM = "bs";
const char RGV_clk[] PROGMEM = "clk";
const char RGV_otr[] PROGMEM = "otr";
const char RGV_wkly[] PROGMEM = "wkly";
const char RGV_su[] PROGMEM = "su";
const char RGV_mo[] PROGMEM = "mo";
const char RGV_tu[] PROGMEM = "tu";
const char RGV_we[] PROGMEM = "we";
const char RGV_th[] PROGMEM = "th";
const char RGV_fr[] PROGMEM = "fr";
const char RGV_sa[] PROGMEM = "sa";
const char RGV_line[] PROGMEM = "line";

const char RGV_dual[] PROGMEM = "dual";
const char RGV_on[] PROGMEM = "on";
const char RGV_ch[] PROGMEM = "ch";
const char RGV_st[] PROGMEM = "st";
const char RGV_off[] PROGMEM = "off";
const char RGV_catv[] PROGMEM = "catv";
const char RGV_sap[] PROGMEM = "sap";
const char RGV_am[] PROGMEM = "am";
const char RGV_aft[] PROGMEM = "aft";
const char RGV_hifi[] PROGMEM = "hifi";
const char RGV_pm[] PROGMEM = "pm";
const char RGV_err[] PROGMEM = "err";
const char RGV_ply[] PROGMEM = "ply";
const char RGV_pply[] PROGMEM = "pply";
const char RGV_fply[] PROGMEM = "fply";
const char RGV_rec[] PROGMEM = "rec";
const char RGV_pse[] PROGMEM = "pse";
const char RGV_ff[] PROGMEM = "ff";
const char RGV_rwd[] PROGMEM = "rwd";

const char RGV_rep[] PROGMEM = "rep";
const char RGV_s[] PROGMEM = "s";
const char RGV_l[] PROGMEM = "l";
const char RGV_p[] PROGMEM = "p";
const char RGV_index[] PROGMEM = "index";
const char RGV_dew[] PROGMEM = "dew";
const char RGV_vps[] PROGMEM = "vps";
const char RGV_pgm[] PROGMEM = "pgm";
const char RGV_1[] PROGMEM = "1";
const char RGV_2[] PROGMEM = "2";
const char RGV_3[] PROGMEM = "3";
const char RGV_4[] PROGMEM = "4";
const char RGV_5[] PROGMEM = "5";
const char RGV_6[] PROGMEM = "6";
const char RGV_7[] PROGMEM = "7";
const char RGV_8[] PROGMEM = "8";

const char RGV_m[] PROGMEM = "m";
const char RGV_h[] PROGMEM = "h";
const char RGV_sek[] PROGMEM = "sek";


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
    RedGreenVcrVfd();
};

#endif
