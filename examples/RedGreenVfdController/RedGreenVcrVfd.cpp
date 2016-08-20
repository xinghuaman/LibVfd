#include "RedGreenVcrVfd.h"

RedGreenVcrVfd::RedGreenVcrVfd()
{
  _bins[0] = 0x02;
  _bins[1] = 0x10;
  _bins[2] = 0x100;
  _bins[3] = 0x1000;
  _bins[4] = 0x2000;
  _bins[5] = 0x8000;
  _bins[6] = 0x10000;
  _bins[7] = 0x40000; 
  _bins[8] = 0x80000;
  _bins[9] = 0x100000;
 _numbins=10;

   digit1.begin(10,PSTR("digit1"));
   digit1.addSegment(&_mostused, _bins+0); //Overflow also on grid 0
   digit1.addSegment(&_mostused, _bins+2);
   digit1.setOverflow(&_ovrflw1);
   digit1.setMinus(&_udash);
   addFunc(&digit1);

   digit2.begin(10,PSTR("digit2"));
   digit2.addSegment(&_mostused, _bins+4);
   digit2.addSegment(&_mostused, _bins+6);
   addFunc(&digit2);

   digit3.begin(10,PSTR("digit3"));
   digit3.addSegment(&_mostused, _bins+8);
   digit3.addSegment(&_mostused, _bins+9);
   addFunc(&digit3);

   digit4.begin(10,PSTR("digit4"));
   digit4.addSegment(&_outsider, _bins+4);
   addFunc(&digit4);

   digit5.begin(10,PSTR("digit5"));
   digit5.addSegment(&_mostused, _bins+5);
   digit5.addSegment(&_outsider, _bins+6);
   addFunc(&digit5);

   digit6.begin(10,PSTR("digit6"));
   digit6.addSegment(&_outsider, _bins+7);
   digit6.addSegment(&_outsider, _bins+8);
   addFunc(&digit6);


  //_mostused.begin(t, tl, tr, m, bl, br, b   , dp);
  _mostused.begin(0x200, 0x80, 0x40, 0x20, 0x08, 0x04, 0x01, 0x00);
  // Almost all digits except
  _outsider.begin( 0x800000, 0x400000, 0x200000, 0x20000, 0x4000, 0x800, 0x400   , 0x00); 
  // Minute last digit seconts all digit



  _l.begin(_bins+1,0x01,PSTR("l")); addFunc(&_l);
  _off.begin(_bins+3,0x01,PSTR("off")); addFunc(&_off);
  _m.begin(_bins+7,0x01,PSTR("m")); addFunc(&_m);

  // 0x02 is grid 0

  _s.begin(_bins+1,0x04,PSTR("s")); addFunc(&_s); 
  _on.begin(_bins+3,0x04,PSTR("on")); addFunc(&_on);
  _dp.begin(_bins+7,0x04,PSTR("dp")); addFunc(&_dp);
 
  // next pin is shorted by the tube so it's skipped.
  
  _p.begin(_bins+1,0x08,PSTR("p")); addFunc(&_p);
  _am.begin(_bins+3,0x08,PSTR("am")); addFunc(&_am);
  _3.begin(_bins+7,0x08,PSTR("3")); addFunc(&_3);

  // 0x10 is grid 1
  // next pin again is shorted by the tube so it's skipped.

  _ff.begin(_bins+1,0x20,PSTR("ff")); addFunc(&_ff);
  _dual.begin(_bins+3,0x20,PSTR("dual")); addFunc(&_dual);
  _5.begin(_bins+7,0x20,PSTR("5")); addFunc(&_5);

  _rep.begin(_bins+1,0x40,PSTR("rep")); addFunc(&_rep);
  _wkly.begin(_bins+3,0x40,PSTR("wkly")); addFunc(&_wkly);
  _we.begin(_bins+7,0x40,PSTR("we")); addFunc(&_we);

  _index.begin(_bins+1,0x80,PSTR("index")); addFunc(&_index);
  _4.begin(_bins+7,0x80,PSTR("4")); addFunc(&_4);
  _pm.begin(_bins+3,0x80,PSTR("pm")); addFunc(&_pm);

  // 0x100 is a grid 2
  // next pin again is shorted by the tube
  
  _cas.begin(_bins+1,0x200,PSTR("cas")); addFunc(&_cas);
  _otr.begin(_bins+3,0x200,PSTR("otr")); addFunc(&_otr);
  _tu.begin(_bins+7,0x200,PSTR("tu")); addFunc(&_tu);

  _ply.begin(_bins+0,0x400,PSTR("ply")); addFunc(&_ply);
   _ch.begin(_bins+2,0x400,PSTR("ch")); addFunc(&_ch);
  _err.begin(_bins+3,0x400,PSTR("err")); addFunc(&_err);
  _sek.begin(_bins+9,0x400,PSTR("sek")); addFunc(&_sek);

  _ovrflw1.begin(_bins+0,0x800,PSTR("ovrflw1")); addFunc(&_ovrflw1);
  _ppse.begin(_bins+1,0x800,PSTR("ppse")); addFunc(&_ppse);
  _line.begin(_bins+2,0x800,PSTR("line")); addFunc(&_line);
  _hifi.begin(_bins+3,0x800,PSTR("hifi")); addFunc(&_hifi);
  _h.begin(_bins+4,0x800,PSTR("h")); addFunc(&_h); //doesn't work!
  _sa.begin(_bins+9,0x800,PSTR("sa")); addFunc(&_sa);

  // 0x1000 is grid 3
  // 0x2000 is grid 4

  _rec.begin(_bins+0,0x4000,PSTR("rec")); addFunc(&_rec);
  _catv.begin(_bins+2,0x4000,PSTR("catv")); addFunc(&_catv);
  _ldash.begin(_bins+3,0x4000,PSTR("ldash")); addFunc(&_ldash);
  _1.begin(_bins+5,0x4000,PSTR("1")); addFunc(&_1);
  _6.begin(_bins+9,0x4000,PSTR("6")); addFunc(&_6);

// 0x8000 is grid 5
// next pin is not connected by the tube
// 0x10000 is grid 6
// next is shorted by the tube

  _pply.begin(_bins+0,0x20000,PSTR("pply")); addFunc(&_pply);
  _bs.begin(_bins+2,0x20000,PSTR("bs")); addFunc(&_bs);
  _vps.begin(_bins+3,0x20000,PSTR("vps")); addFunc(&_vps);
  _8.begin(_bins+9,0x20000,PSTR("8")); addFunc(&_8);


// 0x40000 is grid 7
// 0x80000 is grid 8
// 0x100000 is grid 9

  _udash.begin(_bins+0,0x200000,PSTR("udash")); addFunc(&_udash);
  _pse.begin(_bins+1,0x200000,PSTR("pse")); addFunc(&_pse);
  _clk.begin(_bins+2,0x200000,PSTR("clk")); addFunc(&_clk);
  _sap.begin(_bins+3,0x200000,PSTR("sap")); addFunc(&_sap);
  _mo.begin(_bins+5,0x200000,PSTR("mo")); addFunc(&_mo);
  _fr.begin(_bins+9,0x200000,PSTR("fr")); addFunc(&_fr);

   _fply.begin(_bins+0,0x400000,PSTR("fply")); addFunc(&_fply);
   _aft.begin(_bins+2,0x400000,PSTR("aft")); addFunc(&_aft);
   _dew.begin(_bins+3,0x400000,PSTR("dew")); addFunc(&_dew);
   _2.begin(_bins+5,0x400000,PSTR("2")); addFunc(&_2); 
   _7.begin(_bins+9,0x400000,PSTR("7")); addFunc(&_7);

  _pwr.begin(_bins+0,0x800000,PSTR("pwr")); addFunc(&_pwr);
  _vcr.begin(_bins+2,0x800000,PSTR("vcr")); addFunc(&_vcr);
  _th.begin(_bins+9,0x800000,PSTR("th")); addFunc(&_th);
  _st.begin(_bins+3,0x800000,PSTR("st")); addFunc(&_st);
  _rwd.begin(_bins+1,0x800000,PSTR("rwd")); addFunc(&_rwd); // retest
  _su.begin(_bins+5,0x800000,PSTR("su")); addFunc(&_su);

  _pgm.begin(_bins+5,0x00,PSTR("pgm")); addFunc(&_pgm); // doesnt work
};
