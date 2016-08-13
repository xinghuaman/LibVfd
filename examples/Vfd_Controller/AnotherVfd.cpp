#include "AnotherVfd.h"

AnotherVfd::AnotherVfd()
{
  //AbstractVFD::AbstractVFD();

  _bins[0] = 0x01;
  _bins[1] = 0x02;
  _bins[2] = 0x04;
  _bins[3] = 0x08;
  _numbins=4;
  
  _leftseg.begin(0x10, 0x40, 0x20, 0x80, 0x200, 0x100, 0x400, 0x00);
  _rightseg.begin(0x1000, 0x4000, 0x2000, 0x8000, 0x20000, 0x10000, 0x40000, 0x00);

  digit1.begin(10,global_digit1);
  digit1.addSegment(&_rightseg,_bins+0);
  digit1.addSegment(&_rightseg,_bins+1);
  addFunc(&digit1);

  digit2.begin(10,global_digit2);
  digit2.addSegment(&_leftseg,_bins+2);
  digit2.addSegment(&_rightseg,_bins+2);
  addFunc(&digit2);

  digit3.begin(10,global_digit3);
  digit3.addSegment(&_leftseg,_bins+3);
  digit3.addSegment(&_rightseg,_bins+3);
  addFunc(&digit3);

  _tdvd.begin(global_ani,0x3F0);
  _tdvd.addStep(0x10,_bins+0);
  _tdvd.addStep(0x20,_bins+0);
  _tdvd.addStep(0x40,_bins+0);
  _tdvd.addStep(0x80,_bins+0);
  _tdvd.addStep(0x100,_bins+0);
  _tdvd.addStep(0x200,_bins+0);
  addFunc(&_tdvd);

  _dvdcenter.begin(_bins+0,0x400,global_dvdcenter);
  addFunc(&_dvdcenter);
  _threezero.begin(_bins+0,0x800,global_threezero);
  addFunc(&_threezero);
  _backslash.begin(_bins+0,0x8000,global_backslash);
  addFunc(&_backslash);

  _v.begin(_bins+1,0x10,global_v);
  addFunc(&_v);
  _cd.begin(_bins+1,0x20,global_cd);
  addFunc(&_cd);
  _p.begin(_bins+1,0x40,global_p);
  addFunc(&_p);
  _commas.begin(_bins+1,0x80,global_commas);
  addFunc(&_commas);
  _dash.begin(_bins+1,0x100,global_dash);
  addFunc(&_dash);
  _speakerl.begin(_bins+1,0x200,global_spl);
  addFunc(&_speakerl);
  _speakerr.begin(_bins+1,0x400,global_spr);
  addFunc(&_speakerr);
  _s.begin(_bins+1,0x800,global_s);
  addFunc(&_s);
  _N.begin(_bins+1,0x80000,global_n);
  addFunc(&_N);
  
  _pbc.begin(_bins+2,0x800,global_pbc);
  addFunc(&_pbc);
  _dvd.begin(_bins+2,0x80000,global_dvd);
  addFunc(&_dvd);

  _mp3.begin(_bins+3,0x800,global_mp3);
  addFunc(&_mp3);
  _doublepoint.begin(_bins+3,0x80000,global_dp);
  addFunc(&_doublepoint);

};
