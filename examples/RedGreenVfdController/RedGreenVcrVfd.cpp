#include "RedGreenVcrVfd.h"

RedGreenVcrVfd::RedGreenVcrVfd()
{
  _bins[0] = 0x02; //Power, firstdigit_red, Playsympols
  _bins[1] = 0x10;
  _bins[2] = 0x100;
  _bins[3] = 0x1000;
  _bins[4] = 0x2000;//100000
  _bins[5] = 0x8000;//1 00 00 00
  _bins[6] = 0x10000;//1 00 00 00
  _bins[7] = 0x40000; 
  _bins[8] = 0x80000;
  _bins[9] = 0x100000;
 _numbins=10;

   digit1.begin(10,RGV_digit1);
   digit1.addSegment(&_mostused, _bins+0); //Overflow also on grid 0
   digit1.addSegment(&_mostused, _bins+2);
   addFunc(&digit1);

   digit2.begin(10,RGV_digit2);
   digit2.addSegment(&_mostused, _bins+4);
   digit2.addSegment(&_mostused, _bins+6);
   addFunc(&digit2);

   digit3.begin(10,RGV_digit3);
   digit3.addSegment(&_mostused, _bins+8);
   digit3.addSegment(&_mostused, _bins+9);
   addFunc(&digit3);

   digit4.begin(10,RGV_digit4);
   digit4.addSegment(&_outsider, _bins+4);
   addFunc(&digit4);

   digit5.begin(10,RGV_digit5);
   digit5.addSegment(&_mostused, _bins+5);
   digit5.addSegment(&_outsider, _bins+6);
   addFunc(&digit5);

   digit6.begin(10,RGV_digit6);
   digit6.addSegment(&_outsider, _bins+7);
   digit6.addSegment(&_outsider, _bins+8);
   addFunc(&digit6);


  //_mostused.begin(t, tl, tr, m, bl, br, b   , dp);
  _mostused.begin(0x200, 0x80, 0x40, 0x20, 0x08, 0x04, 0x01, 0x00);
  // Almost all digits except
  _outsider.begin( 0x800000, 0x400000, 0x200000, 0x20000, 0x4000, 0x800, 0x400   , 0x00); 
  // Minute last digit seconts all digit



  _l.begin(_bins+1,0x01,RGV_l); addFunc(&_l);
  _off.begin(_bins+3,0x01,RGV_off); addFunc(&_off);
  _m.begin(_bins+7,0x01,RGV_m); addFunc(&_m);

  // 0x02 is grid 0

  _s.begin(_bins+1,0x04,RGV_s); addFunc(&_s); 
  _on.begin(_bins+3,0x04,RGV_on); addFunc(&_on);
  _dp.begin(_bins+7,0x04,RGV_dp); addFunc(&_dp);
 
  // next pin is shorted by the tube so it's skipped.
  
  _p.begin(_bins+1,0x08,RGV_p); addFunc(&_p);
  _am.begin(_bins+3,0x08,RGV_am); addFunc(&_am);
  _3.begin(_bins+7,0x08,RGV_3); addFunc(&_3);

  // 0x10 is grid 1
  // next pin again is shorted by the tube so it's skipped.

  _ff.begin(_bins+1,0x20,RGV_ff); addFunc(&_ff);
  _dual.begin(_bins+3,0x20,RGV_dual); addFunc(&_dual);
  _5.begin(_bins+7,0x20,RGV_5); addFunc(&_5);

  _rep.begin(_bins+1,0x40,RGV_rep); addFunc(&_rep);
  _wkly.begin(_bins+3,0x40,RGV_wkly); addFunc(&_wkly);
  _we.begin(_bins+7,0x40,RGV_we); addFunc(&_we);

  _index.begin(_bins+1,0x80,RGV_index); addFunc(&_index);
  _4.begin(_bins+7,0x80,RGV_4); addFunc(&_4);
  _pm.begin(_bins+3,0x80,RGV_pm); addFunc(&_pm);

  // 0x100 is a grid 2
  // next pin again is shorted by the tube
  
  _cas.begin(_bins+1,0x200,RGV_cas); addFunc(&_cas);
  _otr.begin(_bins+3,0x200,RGV_otr); addFunc(&_otr);
  _tu.begin(_bins+7,0x200,RGV_tu); addFunc(&_tu);

  _ply.begin(_bins+0,0x400,RGV_ply); addFunc(&_ply);
   _ch.begin(_bins+2,0x400,RGV_ch); addFunc(&_ch);
  _err.begin(_bins+3,0x400,RGV_err); addFunc(&_err);
  _sek.begin(_bins+9,0x400,RGV_sek); addFunc(&_sek);

  _ovrflw1.begin(_bins+0,0x800,RGV_ovrflw1); addFunc(&_ovrflw1);
  _ppse.begin(_bins+1,0x800,RGV_ppse); addFunc(&_ppse);
  _line.begin(_bins+2,0x800,RGV_line); addFunc(&_line);
  _hifi.begin(_bins+3,0x800,RGV_hifi); addFunc(&_hifi);
  _h.begin(_bins+4,0x800,RGV_h); addFunc(&_h); //doesn't work!
  _sa.begin(_bins+9,0x800,RGV_sa); addFunc(&_sa);

  // 0x1000 is grid 3
  // 0x2000 is grid 4

  _rec.begin(_bins+0,0x4000,RGV_rec); addFunc(&_rec);
  _catv.begin(_bins+2,0x4000,RGV_catv); addFunc(&_catv);
  _ldash.begin(_bins+3,0x4000,RGV_ldash); addFunc(&_ldash);
  _1.begin(_bins+5,0x4000,RGV_1); addFunc(&_1);
  _6.begin(_bins+9,0x4000,RGV_6); addFunc(&_6);

// 0x8000 is grid 5
// next pin is not connected by the tube
// 0x10000 is grid 6
// next is shorted by the tube

  _pply.begin(_bins+0,0x20000,RGV_pply); addFunc(&_pply);
  _bs.begin(_bins+2,0x20000,RGV_bs); addFunc(&_bs);
  _vps.begin(_bins+3,0x20000,RGV_vps); addFunc(&_vps);
  _8.begin(_bins+9,0x20000,RGV_8); addFunc(&_8);


// 0x40000 is grid 7
// 0x80000 is grid 8
// 0x100000 is grid 9

  _udash.begin(_bins+0,0x200000,RGV_udash); addFunc(&_udash);
  _pse.begin(_bins+1,0x200000,RGV_pse); addFunc(&_pse);
  _clk.begin(_bins+2,0x200000,RGV_clk); addFunc(&_clk);
  _sap.begin(_bins+3,0x200000,RGV_sap); addFunc(&_sap);
  _mo.begin(_bins+5,0x200000,RGV_mo); addFunc(&_mo);
  _fr.begin(_bins+9,0x200000,RGV_fr); addFunc(&_fr);

   _fply.begin(_bins+0,0x400000,RGV_fply); addFunc(&_fply);
   _aft.begin(_bins+2,0x400000,RGV_aft); addFunc(&_aft);
   _dew.begin(_bins+3,0x400000,RGV_dew); addFunc(&_dew);
   _2.begin(_bins+5,0x400000,RGV_2); addFunc(&_2); 
   _7.begin(_bins+9,0x400000,RGV_7); addFunc(&_7);

  _pwr.begin(_bins+0,0x800000,RGV_pwr); addFunc(&_pwr);
  _vcr.begin(_bins+2,0x800000,RGV_vcr); addFunc(&_vcr);
  _th.begin(_bins+9,0x800000,RGV_th); addFunc(&_th);
  _st.begin(_bins+3,0x800000,RGV_st); addFunc(&_st);
  _rwd.begin(_bins+1,0x800000,RGV_rwd); addFunc(&_rwd); // retest
  _su.begin(_bins+5,0x800000,RGV_su); addFunc(&_su);

  _pgm.begin(_bins+5,0x00,RGV_pgm); addFunc(&_pgm); // doesnt work
};
