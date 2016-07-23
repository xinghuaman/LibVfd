int dataPin = 2;
int latchPin = 3;
int clockPin = 4;

/**
 * Writes Data to chained 595-Shiftregisters
 * Let b_i,j be the j-th bit in the i-th Bytes.
 * Bytes are numbered like array positions in buffer.
 * bits are numbered MSB first.
 * Let Q_k,l be the l-th Output of the k_th Chip.
 * Chips are numbered like their position in the chain. First Chip is the one
 * connected to the Arduino.
 * Then the bits correspond to Pinouts like this:
 * Q_i,j = b_i,j
 */
 
class Shifter {
  private:
    int _dataPin;
    int _latchPin;
    int _clockPin;
    unsigned long
    
  public:
    Shifter(int dataPin, int latchPin, int clockPin);
    void begin();
    void write(byte* buffer, int numBytes);
};

Shifter::Shifter(int dataPin, int latchPin, int clockPin){
  _dataPin = dataPin;
  _latchPin = latchPin;
  _clockPin = clockPin;

}

void Shifter::begin(){
  pinMode(dataPin,OUTPUT);
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void Shifter::write(unsigned long toWrite){
 
     digitalWrite(latchPin,LOW);
     for (int i=3;i>=0;i--){
       byte theByte = (byte) (toWrite >> (i*8));
       Serial.println(theByte,HEX);
       shiftOut(dataPin, clockPin, MSBFIRST, theByte);
     }
     digitalWrite(latchPin, HIGH);
 
}

Shifter shifter(2,3,4);

void setup() {
  
  Serial.begin(9600);
  shifter.begin();
  
}

void loop(){
 
   if (Serial.available()>0) {
       String stringcoming = Serial.readString();
       unsigned long incoming = strtol(stringcoming.c_str(),NULL,16);
       incoming = ~incoming;
       
       
       
       
       shifter.write(incoming);
       
       //buffer[0]=incoming;
       //Serial.println(buffer[0],HEX);
       //digitalWrite(latchPin,LOW);
       //shiftOut(dataPin, clockPin, MSBFIRST, buffer[0]);
       //digitalWrite(latchPin, HIGH);
       
    }

}
