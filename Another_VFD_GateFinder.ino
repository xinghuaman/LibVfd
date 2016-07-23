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
     _masks[0x09] = top | topRight |  middle | bottom | bottomLeft | topLeft; 
};

unsigned long SevenSegments::getMaskForDigit(byte digit) {
  if (digit > 10) return 0L;
  unsigned long ret = _masks[digit];
  Serial.print("digit -- mask: ");
  Serial.print(digit);
  Serial.print(" -- ");
  Serial.println(ret);
  return ret;
};

unsigned long SevenSegments::getMaskForClearing(){
  return _masks[8] | _decimalPoint;
}

class SevenSegmentEncoder {
  private:
    SevenSegments* _mySegments;
    byte _numSegments;
    byte _radix;
  
  public:
    void begin(SevenSegments* mySegments, byte numSegments, byte radix);
    void encode(int number, unsigned long* buffer);
};

void SevenSegmentEncoder::begin(SevenSegments* mySegments, byte numSegments, byte radix) {
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



class AnotherVFD {
  private:
    unsigned long _bins[4];
    unsigned long _grids[4];
    
    //Several Grids
    SevenSegments _rightseg;
    SevenSegments _leftseg;
    SevenSegments _segments[2];
    SevenSegments _segments2[2];
    SevenSegmentEncoder _encoder;
    SevenSegmentEncoder _encoder2;
   
    
    //Grid 0
    
    //Grid 1
    
    //Grid 2
    
    //Grid 3
    unsigned long _dvd[6];
    
   void doSetDigit(int number, int binleft, int binright, int swapem);
   
  public:
    AnotherVFD();
    unsigned long* getBins();
   void setDigit(int digit, int number);
};

AnotherVFD::AnotherVFD()
{
  _grids[3] = 0x01;
  _grids[2] = 0x02;
  _grids[1] = 0x04;
  _grids[0] = 0x08;
  
  for(int i=0;i<4;i++)
    _bins[i]|=_grids[i];

  
  _dvd[0] = 0x10;
  _rightseg.begin(0x400, 0x100, 0x200, 0x80, 0x20, 0x40, 0x10, 0x00);
  _leftseg.begin(0x40000, 0x10000, 0x20000, 0x8000, 0x2000, 0x4000, 0x1000, 0x00);
  _segments[0]=_leftseg;
  _segments[1]=_rightseg;
  _encoder.begin(_segments,2,10);
  _segments2[0]=_leftseg;
  _segments2[1]=_leftseg;
  _encoder2.begin(_segments2,2,10);
}

unsigned long* AnotherVFD::getBins() {
  return _bins;
}

void AnotherVFD::setDigit(int digit, int number){
   switch(digit){
      case 1:
        doSetDigit(number,0,0,0);
        break;
      case 2:
        doSetDigit(number,1,1,0);
        break;
      case 3:
        _bins[3]&=~_rightseg.getMaskForClearing();
        _bins[2]&=~_rightseg.getMaskForClearing();
        unsigned long buffer[2];
        _encoder2.encode(number,buffer);
        _bins[2]|=buffer[0];
        _bins[3]|=buffer[1];
        break;
   }
}

void AnotherVFD::doSetDigit(int number, int binleft, int binright, int swapem){

  _bins[binright]&=~_rightseg.getMaskForClearing();
  _bins[binleft]&=~_leftseg.getMaskForClearing();
  
  unsigned long buffer[2];
  _encoder.encode(number, buffer);
  
  _bins[binleft]|=buffer[0^swapem];
  _bins[binright]|=buffer[1^swapem];
  
}


Shifter shifter(2,3,4,0);
AnotherVFD anotherVFD;
AnotherMultiplexer plexi(&shifter, anotherVFD.getBins(), 4);


void setup() {
  
  Serial.begin(9600);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerRoutine);
  shifter.begin();
  pinMode(13,OUTPUT);
}      

boolean pinState13=false;
int counter=0;

void timerRoutine(){
  if (counter > 1000) {
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

       if (stringcoming.substring(0,3).equals("d1=")) {
         Serial.print("Setting digit one =");
         String numberPart = stringcoming.substring(3);
         int number = strtoul(numberPart.c_str(),NULL,10);
         Serial.println(number);
         anotherVFD.setDigit(1,number);
       }
        if (stringcoming.substring(0,3).equals("d2=")) {
         Serial.print("Setting digit one =");
         String numberPart = stringcoming.substring(3);
         int number = strtoul(numberPart.c_str(),NULL,10);
         Serial.println(number);
         anotherVFD.setDigit(2,number);
       }
       if (stringcoming.substring(0,3).equals("d3=")) {
         Serial.print("Setting digit one =");
         String numberPart = stringcoming.substring(3);
         int number = strtoul(numberPart.c_str(),NULL,10);
         Serial.println(number);
         anotherVFD.setDigit(3,number);
       }

    }

}
