//**************************************************************//
//  Name    : shiftOutCode, Hello World                                
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis 
//  Date    : 25 Oct, 2006    
//  Modified: 23 Mar 2010                                 
//  Version : 2.0                                             
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                           
//****************************************************************

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;



void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  Serial.begin(9600);

  
}

int counter=0;
int bins[12];
int mcounter=0;

void outBin(int binnum){
  // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, bins[binnum*3+0]);  
    shiftOut(dataPin, clockPin, MSBFIRST, bins[binnum*3+1]);
    shiftOut(dataPin, clockPin, MSBFIRST, bins[binnum*3+2]);

    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    delay(5);
}

void loop() {
 
    if (Serial.available()>0) {
       int incoming = Serial.read();
       Serial.print("Byte ");
       Serial.print(counter);
       Serial.print(": ");
       Serial.println(incoming,HEX);
       
       bins[counter]=incoming;
       
       counter++;
       if(counter==12) counter=0;
    }
    
    outBin(mcounter);
    mcounter++;
    if (mcounter==4) mcounter=0;
  
   
    
 
    
}
