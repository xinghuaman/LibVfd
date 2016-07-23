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

void Shifter::write(byte* buffer, int numBytes){
  for(byte* toWrite = buffer + numBytes -1; toWrite >= buffer; toWrite--){
     digitalWrite(latchPin,LOW);
     shiftOut(dataPin, clockPin, MSBFIRST, *toWrite);
     digitalWrite(latchPin, HIGH);
  }
}

Shifter shifter(2,3,4);

void setup() {
  
  Serial.begin(9600);
  shifter.begin();
  
}

void loop(){
 
   if (Serial.available()>0) {
       String stringcoming = Serial.readString();
       long incoming = strtol(stringcoming.c_str(),NULL,16);
       incoming = ~incoming;
       
       byte* buffer = (byte*) &incoming;
       
       for (int i=0;i<4;i++){
          Serial.print(" Byte ");
          Serial.print(i);
          Serial.print(": ");
          Serial.print(buffer[i],HEX);    
       }
       Serial.println();
       shifter.write(buffer,3);
       
       //buffer[0]=incoming;
       //Serial.println(buffer[0],HEX);
       //digitalWrite(latchPin,LOW);
       //shiftOut(dataPin, clockPin, MSBFIRST, buffer[0]);
       //digitalWrite(latchPin, HIGH);
       
    }

}
