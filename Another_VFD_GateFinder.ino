#include <TimerOne.h>

int dataPin = 2;
int latchPin = 3;
int clockPin = 4;

 
 class SevenSegments {
  private:
    unsigned long _masks[0xF];
    unsigned long _middle;
    unsigned long _decimalPoint;
  
  public:
    void begin(
       unsigned long top,
       unsigned long topLeft,
       unsigned long topRight,
       unsigned long middle,
       unsigned long bottomLeft,
       unsigned long bottomRight,
       unsigned long bottom,
       unsigned long decimalPoint
     );
     
    unsigned long getMaskForDigit(byte digit);
    unsigned long getMaskForClearing();
};

void SevenSegments::begin (
       unsigned long top,
       unsigned long topLeft,
       unsigned long topRight,
       unsigned long middle,
       unsigned long bottomLeft,
       unsigned long bottomRight,
       unsigned long bottom,
       unsigned long decimalPoint
     ) {
     _middle = middle;
     _decimalPoint = decimalPoint;
     _masks[0x00] = top | topLeft | bottomLeft | bottom | bottomRight | topRight;
     _masks[0x01] = topRight | bottomRight;
     _masks[0x02] = top | topRight | middle | bottomLeft | bottom;
     _masks[0x03] = top | topRight | middle | bottomRight | bottom;
     _masks[0x04] = topLeft | topRight | middle | bottomRight;
     _masks[0x05] = top | topLeft | middle | bottomRight | bottom;
     _masks[0x06] = top | topLeft | middle | bottomRight | bottom | bottomLeft;
     _masks[0x07] = top | topRight | bottomRight;
     _masks[0x08] = top | topRight |  middle | bottomRight | bottom | bottomLeft | topLeft;
     _masks[0x09] = top | topRight |  middle | bottom | bottomRight | topLeft; 
};

unsigned long SevenSegments::getMaskForDigit(byte digit) {
  Serial.print("Mask for Digit: ");
  Serial.println(digit);
  if (digit > 10) return 0L;
  unsigned long ret = _masks[digit];
  return ret;
};

unsigned long SevenSegments::getMaskForClearing(){
  return _masks[8] | _decimalPoint;
}

class SevenSegmentEncoder {
  private:
    SevenSegments* _mySegments[5];
    unsigned long* _myBins[5];

    byte _numSegments;
    byte _radix;
  
  public:
    void begin(byte radix);
    void addSegment(SevenSegments* segment, unsigned long* bin);
    void encode(int number);
};

void SevenSegmentEncoder::begin(byte radix) {
  _radix = radix;
};

void SevenSegmentEncoder::addSegment(SevenSegments* segment, unsigned long* bin){
  _mySegments[_numSegments]=segment;
  _myBins[_numSegments]=bin;
  _numSegments++;
}

void SevenSegmentEncoder::encode(int number) {
  Serial.print("Trying to encode: ");
  Serial.println(number);
  if (number < 0 ) {
    number = -number;
    //TODO: Handle numbersign.
  }
  
  for (int i=_numSegments-1; i>=0; i--) {
    Serial.println(i);
    byte digit = number % _radix;
    number = number / _radix;
    (*_myBins[i]) |= _mySegments[i]->getMaskForDigit(digit);
  }
  //TODO: Handle overflow
};

 
 
class Shifter {
  private:
    int _dataPin;
    int _latchPin;
    int _clockPin;
    unsigned long _invertMask;
    
  public:
    Shifter(int dataPin, int latchPin, int clockPin, unsigned long);
    void begin();
    void write(unsigned long);
};

Shifter::Shifter(int dataPin, int latchPin, int clockPin, unsigned long invertMask){
  _dataPin = dataPin;
  _latchPin = latchPin;
  _clockPin = clockPin;
  _invertMask = invertMask;

}

void Shifter::begin(){
  pinMode(dataPin,OUTPUT);
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void Shifter::write(unsigned long toWrite){
 
      toWrite ^= _invertMask;
  
     digitalWrite(latchPin,LOW);
     for (int i=3;i>=0;i--){
       byte theByte = (byte) (toWrite >> (i*8));
       //Serial.println(theByte,HEX);
       shiftOut(dataPin, clockPin, MSBFIRST, theByte);
     }
     digitalWrite(latchPin, HIGH);
 
}

class AnotherMultiplexer {
  private:
    Shifter* _shifter;
    unsigned long* _bins;
    byte _currentBin;
    byte _numBins;
    
    
  public:
    AnotherMultiplexer(Shifter* shifter, unsigned long* bins, byte numBins);
    void cycle();
}; 

AnotherMultiplexer::AnotherMultiplexer(Shifter* shifter, unsigned long* bins, byte numBins){
   _shifter = shifter;
   _bins = bins;
   _numBins = numBins;
};

void AnotherMultiplexer::cycle() {
  _shifter->write(_bins[_currentBin++]);
  if (_currentBin >= _numBins) _currentBin = 0;
}

class SingleFunction {
  private:
    unsigned long* _bin;
    String _memonic;
    unsigned long _mask;
    
  public:
    void begin(unsigned long*, unsigned long mask, String memonic);
    boolean tryObey(String command);
    String getMemonic();
};

void SingleFunction::begin(unsigned long* targetBin, unsigned long mask, String memonic) {
  _bin=targetBin;
  _mask=mask;
  _memonic=memonic;
};

boolean SingleFunction::tryObey(String command){
  if (_memonic.equals(command.substring(0,_memonic.length()))) {
    String wantsOnOrOff = command.substring(_memonic.length()+1,_memonic.length()+2);   
    if (wantsOnOrOff.equals("1")) {
      (*_bin)|=_mask;
    } else {
      (*_bin)&=~_mask;
    }
    return true;
  }
  return false;
};

String SingleFunction::getMemonic() {
  return _memonic;
}

class DigitCommandParser {
  private:
    String _memonic;
    SevenSegmentEncoder* _encoder;
  
  public:
    void begin(String memonic, SevenSegmentEncoder* encoder);
    boolean tryObey(String command);
    String getMemonic();
};

void DigitCommandParser::begin(String memonic, SevenSegmentEncoder *encoder) {
  _memonic = memonic;
  _encoder = encoder;
}

boolean DigitCommandParser::tryObey(String command) {
  if (command.substring(0,_memonic.length()).equals(_memonic)) {
     Serial.print("Command: ");
     Serial.println(command);
     String numberPart = command.substring(_memonic.length()+1,command.length()-1);
     Serial.print("Numberpart: ");
     Serial.println(numberPart);
     if (numberPart.equals("off")) {
       
     } else {
       int number = strtoul(numberPart.c_str(),NULL,10);
       Serial.println(number);
       Serial.println((unsigned long)_encoder,HEX);
       _encoder->encode(number);
    }
    return true;
  }
  return false;
  
};

String DigitCommandParser::getMemonic() {
  return _memonic;
}

class AnotherVFD {
  private:
    unsigned long _bins[4];
    
    //Several Grids
    SevenSegments _rightseg;
    SevenSegments _leftseg;
    SevenSegmentEncoder _encoder[3];
    DigitCommandParser _parsers[3];
   
    //Gate 0
    unsigned long _dvd[6];
    unsigned long _dvdcenter = 0x400;
    unsigned long _dvdOffMask = 0x3F0;
    
    SingleFunction _singlefunctions[10];
    int _numSingleFunctions=0;
    
    //Gate 1
    unsigned long v = 0x10;
    unsigned long cd= 0x20;
    unsigned long p = 0x40;
    unsigned long commas = 0x80;
    unsigned long speakerLeft = 0x200;
    unsigned long speakerRight = 0x400;
    unsigned long middleDash = 0x100;
    
    byte dvdAnimationCounter=0;
   
  public:
    AnotherVFD();
    unsigned long* getBins();
    void stepDvdAnimation();
    void dvdOff();
    void tryObey(String command);
};

AnotherVFD::AnotherVFD()
{
  _bins[0] = 0x01;
  _bins[1] = 0x02;
  _bins[2] = 0x04;
  _bins[3] = 0x08;

  
  _dvd[0]=0x10;
  _dvd[1]=0x20;
  _dvd[2]=0x40;
  _dvd[3]=0x80;
  _dvd[4]=0x100;
  _dvd[5]=0x200;
  
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
  
  
  _singlefunctions[_numSingleFunctions]=SingleFunction();
  _singlefunctions[_numSingleFunctions++].begin(_bins+1,0x10,"v");
};

void AnotherVFD::tryObey(String command) {
  for(int i=0;i<_numSingleFunctions;i++) {
    if (_singlefunctions[i].tryObey(command)) return;
  }
  for(int i=0;i<3;i++) {
    if (_parsers[i].tryObey(command)) return;
  }
};

unsigned long* AnotherVFD::getBins() {
  return _bins;
};

void AnotherVFD::stepDvdAnimation(){
  _bins[0]|=_dvdOffMask;
  _bins[0]&=~_dvd[dvdAnimationCounter++];
  _bins[0]^=_dvdcenter;
  if (dvdAnimationCounter>=6)
    dvdAnimationCounter=0;
};

void AnotherVFD::dvdOff(){
  _bins[3]&=~_dvdOffMask;
}

Shifter shifter(2,3,4,0);
AnotherVFD anotherVFD;
AnotherMultiplexer plexi(&shifter, anotherVFD.getBins(), 4);


void setup() {
  
  Serial.begin(9600);
  Timer1.initialize(2000);
  Timer1.attachInterrupt(timerRoutine);
  shifter.begin();
  pinMode(13,OUTPUT);
}      

boolean pinState13=false;
int counter=0;

void timerRoutine(){
  if (counter > 50) {
    anotherVFD.stepDvdAnimation();
    digitalWrite(13,pinState13);
    pinState13=~pinState13;
    counter=0;
  } else {
    counter++;
  }
  plexi.cycle();
}

void loop(){
 
   if (Serial.available()>0) {
       String stringcoming = Serial.readString();

       anotherVFD.tryObey(stringcoming);

    }

}
