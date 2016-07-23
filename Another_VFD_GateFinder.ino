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
    SevenSegments(
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
};

SevenSegments::SevenSegments( 
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
     _masks[0x09] = top | topRight |  middle | bottom | bottomLeft | topLeft; 
};

unsigned long SevenSegments::getMaskForDigit(byte digit) {
  if (digit > 10) return 0L;
  return _masks[digit];
};

class SevenSegmentEncoder {
  private:
    SevenSegments* _mySegments;
    byte _numSegments;
    byte _radix;
  
  public:
    SevenSegmentEncoder(SevenSegments* mySegments, byte numSegments, byte radix);
    void encode(int number, unsigned long* buffer);
};

SevenSegmentEncoder::SevenSegmentEncoder(SevenSegments* mySegments, byte numSegments, byte radix) {
  _mySegments = mySegments;
  _numSegments = numSegments;
  _radix = radix;
};

void SevenSegmentEncoder::encode(int number, unsigned long* buffer) {
  if (number < 0 ) {
    number = -number;
    //TODO: Handle numbersign.
  }
  
  for (int i=_numSegments-1; i>=0; i--) {
    byte digit = number % _radix;
    number = number / _radix;
    buffer[i] = _mySegments[i].getMaskForDigit(digit);
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
       Serial.println(theByte,HEX);
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



class AnotherVFD {
  private:
    unsigned long _bins[4];
    unsigned long _grids[4];
    
    //Several Grids
    SevenSegments _rightseg;
    SevenSegments  _leftseg;

    
    //Grid 0
    
    //Grid 1
    
    //Grid 2
    
    //Grid 3
    unsigned long _dvd[6];
  
  public:
    AnotherVFD();
    unsigned long* getBins();
};

AnotherVFD::AnotherVFD() :
_rightseg(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00),
 _leftseg(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
{
  _grids[3] = 0x01;
  _grids[2] = 0x02;
  _grids[1] = 0x04;
  _grids[0] = 0x08;
  
  _dvd[0] = 0x10;
}

Shifter shifter(2,3,4,0x0000000F);

unsigned long bins[4];

AnotherMultiplexer plexi(&shifter, bins, 4);


void setup() {
  
  Serial.begin(9600);
  Timer1.initialize(12000);
  Timer1.attachInterrupt(timerRoutine);
  shifter.begin();
  
}

void timerRoutine(){
  
}

void loop(){
 
   if (Serial.available()>0) {
       String stringcoming = Serial.readString();
       unsigned long incoming = strtol(stringcoming.c_str(),NULL,16);
  
       shifter.write(incoming);

    }

}
