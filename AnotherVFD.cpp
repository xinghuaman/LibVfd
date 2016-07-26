#include <AnotherVFD.h>

void AnotherVFD::addSingleFunction(int bin, unsigned long mask, String memonic) {
  _singlefunctions[_numSingleFunctions]=SingleFunction();
  _singleParsers[_numSingleFunctions]=SingleFunctionCommandParser();
  _singleParsers[_numSingleFunctions].begin(_singlefunctions+_numSingleFunctions);
  _singlefunctions[_numSingleFunctions++].begin(_bins+bin,mask,memonic);
}

AnotherVFD::AnotherVFD()
{
  _bins[0] = 0x01;
  _bins[1] = 0x02;
  _bins[2] = 0x04;
  _bins[3] = 0x08;
  
  _leftseg.begin(0x10, 0x40, 0x20, 0x80, 0x200, 0x100, 0x400, 0x00);
  _rightseg.begin(0x1000, 0x4000, 0x2000, 0x8000, 0x20000, 0x10000, 0x40000, 0x00);
  
  _encoder[0] = SevenSegmentEncoder();
  _encoder[0].begin(10);
  _encoder[0].addSegment(&_rightseg,_bins+0);
  _encoder[0].addSegment(&_rightseg,_bins+1);
  _parsers[0] = DigitCommandParser();
  _parsers[0].begin("digit1",_encoder+0);
  
  _encoder[1] = SevenSegmentEncoder();
  _encoder[1].begin(10);
  _encoder[1].addSegment(&_leftseg, _bins+2);
  _encoder[1].addSegment(&_rightseg,_bins+2);
  _parsers[1] = DigitCommandParser();
  _parsers[1].begin("digit2",_encoder+1);
  
  _encoder[2] = SevenSegmentEncoder();
  _encoder[2].begin(10);
  _encoder[2].addSegment(&_leftseg, _bins+3);
  _encoder[2].addSegment(&_rightseg,_bins+3);
  _parsers[2] = DigitCommandParser();
  _parsers[2].begin("digit3",_encoder+2);
  
  _tdvd.begin("animate",0x3F0);
  _tdvd.addStep(0x10,_bins+0);
  _tdvd.addStep(0x20,_bins+0);
  _tdvd.addStep(0x40,_bins+0);
  _tdvd.addStep(0x80,_bins+0);
  _tdvd.addStep(0x100,_bins+0);
  _tdvd.addStep(0x200,_bins+0);
 
  addSingleFunction(0,0x400,"dvdcenter");
 
  addSingleFunction(0,0x800,"3.0");
  addSingleFunction(0,0x80000,"\\");
  
  
  addSingleFunction(1,0x10,"v");
  addSingleFunction(1,0x20,"cd");
  addSingleFunction(1,0x40,"p");
  addSingleFunction(1,0x80,"commas");
  addSingleFunction(1,0x100,"dash");
  addSingleFunction(1,0x200,"speakerl");
  addSingleFunction(1,0x400,"speakerr");
  addSingleFunction(1,0x800,"S");
  addSingleFunction(1,0x80000,"N");
  
  
  addSingleFunction(2,0x800,"pbc");
  addSingleFunction(2,0x80000,"dvd");
  
  
  addSingleFunction(3,0x800,"mp3");
  addSingleFunction(3,0x80000,":");


};

void AnotherVFD::tryObey(String command) {
  for(int i=0;i<_numSingleFunctions;i++) {
    if (_singleParsers[i].tryObey(command)) return;
  }
  for(int i=0;i<3;i++) {
    if (_parsers[i].tryObey(command)) return;
  }
  Serial.print("Unrecognized: ");
  Serial.print(command);
};

unsigned long* AnotherVFD::getBins() {
  return _bins;
};

void AnotherVFD::animate(){
  _tdvd.animate();
  for(int i=0;i<_numSingleFunctions;i++){
    _singlefunctions[i].animate();
  }
};
