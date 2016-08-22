#include "DvdVfd.h"

DvdVfd::DvdVfd()
{
  //AbstractVFD::AbstractVFD();

  _bins[0] = 0x01;
  _bins[1] = 0x02;
  _bins[2] = 0x04;
  _bins[3] = 0x08;
  _numbins=4;
  
  _leftseg.begin(0x10, 0x40, 0x20, 0x80, 0x200, 0x100, 0x400, 0x00);
  _rightseg.begin(0x1000, 0x4000, 0x2000, 0x8000, 0x20000, 0x10000, 0x40000, 0x00);

  digit1.begin(10,PSTR("digit1"));
  digit1.addSegment(&_rightseg,_bins+0);
  digit1.addSegment(&_rightseg,_bins+1);
  addFunc(&digit1);

  digit2.begin(10,PSTR("digit2"));
  digit2.addSegment(&_leftseg,_bins+2);
  digit2.addSegment(&_rightseg,_bins+2);
  addFunc(&digit2);

  digit3.begin(10,PSTR("digit3"));
  digit3.addSegment(&_leftseg,_bins+3);
  digit3.addSegment(&_rightseg,_bins+3);
  addFunc(&digit3);

  _tdvd.begin(PSTR("ani"),0x3F0);
  _tdvd.addStep(0x10,_bins+0);
  _tdvd.addStep(0x20,_bins+0);
  _tdvd.addStep(0x40,_bins+0);
  _tdvd.addStep(0x80,_bins+0);
  _tdvd.addStep(0x100,_bins+0);
  _tdvd.addStep(0x200,_bins+0);
  addFunc(&_tdvd);

  _dvdcenter.begin(_bins+0,0x400,PSTR("dvdcenter"));
  addFunc(&_dvdcenter);
  _threezero.begin(_bins+0,0x800,PSTR("threezero"));
  addFunc(&_threezero);
  _backslash.begin(_bins+0,0x8000,PSTR("backslash"));
  addFunc(&_backslash);

  _v.begin(_bins+1,0x10,PSTR("v"));
  addFunc(&_v);
  _cd.begin(_bins+1,0x20,PSTR("cd"));
  addFunc(&_cd);
  _p.begin(_bins+1,0x40,PSTR("p"));
  addFunc(&_p);
  _commas.begin(_bins+1,0x80,PSTR("commas"));
  addFunc(&_commas);
  _dash.begin(_bins+1,0x100,PSTR("dash"));
  addFunc(&_dash);
  _speakerl.begin(_bins+1,0x200,PSTR("spl"));
  addFunc(&_speakerl);
  _speakerr.begin(_bins+1,0x400,PSTR("spr"));
  addFunc(&_speakerr);
  _s.begin(_bins+1,0x800,PSTR("s"));
  addFunc(&_s);
  _N.begin(_bins+1,0x80000,PSTR("n"));
  addFunc(&_N);
  
  _pbc.begin(_bins+2,0x800,PSTR("pbc"));
  addFunc(&_pbc);
  _dvd.begin(_bins+2,0x80000,PSTR("dvd"));
  addFunc(&_dvd);

  _mp3.begin(_bins+3,0x800,PSTR("mp3"));
  addFunc(&_mp3);
  _doublepoint.begin(_bins+3,0x80000,PSTR("dp"));
  addFunc(&_doublepoint);

};
