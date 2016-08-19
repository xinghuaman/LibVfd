#include "RedGreenVcrVfd.h"

RedGreenVcrVfd::RedGreenVcrVfd()
{
  _bins[0] = 0x02; //Power, firstdigit_red, Playsympols
  _bins[1] = 0x20;
  _bins[2] = 0x400;
  _bins[3] = 0x8000;
  _bins[4] = 0x10000;//100000
  _bins[5] = 0x40000;//1 00 00 00
  _bins[6] = 0x100000;//1 00 00 00
  _bins[7] = 0x800000; 
  _bins[8] = 0x1000000;
  _bins[9] = 0x2000000;
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
  _mostused.begin(0x1000, 0x200, 0x100, 0x80, 0x10, 0x04, 0x01, 0x00);
  // Almost all digits except
  _outsider.begin( 0x10000000, 0x8000000, 0x4000000, 0x400000, 0x20000, 0x4000, 0x2000   , 0x00); 
  // Minute last digit seconts all digit



  _l.begin(_bins+1,0x01,RGV_l); addFunc(&_l);
  
  _m.begin(_bins+7,0x01,RGV_m); addFunc(&_m);
  _off.begin(_bins+3,0x01,RGV_off); addFunc(&_off);

  _su.begin(_bins+5,0x04,RGV_su); addFunc(&_su);// Does not work!
  _on.begin(_bins+3,0x04,RGV_on); addFunc(&_on);
  _dp.begin(_bins+7,0x04,RGV_dp); addFunc(&_dp);
  _s.begin(_bins+1,0x04,RGV_s); addFunc(&_s); 
 
  // 0x08 shorted by the tube
  
  _p.begin(_bins+1,0x10,RGV_p); addFunc(&_p);
  _am.begin(_bins+3,0x10,RGV_am); addFunc(&_am);
  _3.begin(_bins+7,0x10,RGV_3); addFunc(&_3);

  // 0x20 is a grid
  // 0x40 is shorted by the tube

  _5.begin(_bins+7,0x80,RGV_5); addFunc(&_5);
  _ff.begin(_bins+1,0x80,RGV_ff); addFunc(&_ff);
  _dual.begin(_bins+3,0x80,RGV_dual); addFunc(&_dual);

  _wkly.begin(_bins+3,0x100,RGV_wkly); addFunc(&_wkly);
  _rep.begin(_bins+1,0x100,RGV_rep); addFunc(&_rep);
  _we.begin(_bins+7,0x100,RGV_we); addFunc(&_we);

  _index.begin(_bins+1,0x200,RGV_index); addFunc(&_index);
  _4.begin(_bins+7,0x200,RGV_4); addFunc(&_4);
  _pm.begin(_bins+3,0x200,RGV_pm); addFunc(&_pm);

  // 0x400 is a grid
  // 0x800 is shorted by the tube
  
  _cas.begin(_bins+1,0x1000,RGV_cas); addFunc(&_cas);
  _otr.begin(_bins+3,0x1000,RGV_otr); addFunc(&_otr);
  _tu.begin(_bins+7,0x1000,RGV_tu); addFunc(&_tu);

   _ch.begin(_bins+2,0x2000,RGV_ch); addFunc(&_ch);
  _ply.begin(_bins+0,0x2000,RGV_ply); addFunc(&_ply);
  _err.begin(_bins+3,0x2000,RGV_err); addFunc(&_err);
  _sek.begin(_bins+9,0x2000,RGV_sek); addFunc(&_sek);

  //Overflow is 4000,
  _line.begin(_bins+2,0x4000,RGV_line); addFunc(&_line);
  _hifi.begin(_bins+3,0x4000,RGV_hifi); addFunc(&_hifi);
  //Additional symbols for pause like on 4000 too.
  //_h.begin(_bins+0,0x4000,RGV_h); addFunc(&_h);
  _sa.begin(_bins+9,0x4000,RGV_sa); addFunc(&_sa);

  // 0x  80 00 is a grid
  // 0x1 00 00 is a grid



  _rec.begin(_bins+0,0x20000,RGV_rec); addFunc(&_rec);
  _catv.begin(_bins+2,0x20000,RGV_catv); addFunc(&_catv);
  //Lowerdash is 20000
  //_1.begin(_bins+1,0x20000,RGV_1); addFunc(&_1); // does not work
  _6.begin(_bins+9,0x20000,RGV_6); addFunc(&_6);

// 0x 4 00 00 is a grid
// 0x 8 00 00 is not connected by the tube
// 0x10 00 00 is a grid
// 0x20 00 00 is shorted by the tube

  _vps.begin(_bins+3,0x400000,RGV_vps); addFunc(&_vps);
  _8.begin(_bins+9,0x400000,RGV_8); addFunc(&_8);
  //_bs.begin(_bins+0,0x400000,RGV_bs); addFunc(&_bs);
  _pply.begin(_bins+0,0x400000,RGV_pply); addFunc(&_pply);

// 0x  80 00 00 is a gate
// 0x1 00 00 00 is a gate
// 0x2 00 00 00 is a gate



  _mo.begin(_bins+5,0x4000000,RGV_mo); addFunc(&_mo);
  _clk.begin(_bins+2,0x4000000,RGV_clk); addFunc(&_clk);
  _fr.begin(_bins+9,0x4000000,RGV_fr); addFunc(&_fr);
  _sap.begin(_bins+3,0x4000000,RGV_sap); addFunc(&_sap);
  //_pse.begin(_bins+1,0x4000000,RGV_pse); addFunc(&_pse);
  // upper minus is at 0x4 00 00 00

  // lower minus is on grid 3


   _fply.begin(_bins+0,0x8000000,RGV_fply); addFunc(&_fply);
   _aft.begin(_bins+2,0x8000000,RGV_aft); addFunc(&_aft);
   _dew.begin(_bins+3,0x8000000,RGV_dew); addFunc(&_dew);
   //_2.begin(_bins+1,0x8000000,RGV_2); addFunc(&_2); // Todo!
   _7.begin(_bins+9,0x8000000,RGV_7); addFunc(&_7);

  _pwr.begin(_bins+0,0x10000000,RGV_pwr); addFunc(&_pwr);
  _vcr.begin(_bins+2,0x10000000,RGV_vcr); addFunc(&_vcr);
  //_su.begin(_bins+0,0x10000000,RGV_su); addFunc(&_su);
  _th.begin(_bins+9,0x10000000,RGV_th); addFunc(&_th);
  _st.begin(_bins+3,0x10000000,RGV_st); addFunc(&_st);
  _rwd.begin(_bins+0,0x10000000,RGV_rwd); addFunc(&_rwd);
  //_pwr.begin(_bins+0,0x10000000,RGV_pwr); addFunc(&_pwr);

  _pgm.begin(_bins+5,0x00,RGV_pgm); addFunc(&_pgm);
};
