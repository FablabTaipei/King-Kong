/* code for max 7219 from maxim,
reduced and optimised for useing more then one 7219 in a row,
______________________________________

 Code History:
 --------------

The orginal code was written for the Wiring board by:
 * Nicholas Zambetti and Dave Mellis /Interaction Design Institute Ivrea /Dec 2004
 * http://www.potemkin.org/uploads/Wiring/MAX7219.txt

First modification by:
 * Marcus Hannerstig/  K3, malmö högskola /2006
 * http://www.xlab.se | http://arduino.berlios.de

This version is by:
 * tomek ness /FH-Potsdam / Feb 2007
 * http://design.fh-potsdam.de/

 * @acknowledgements: eric f.

-----------------------------------

General notes:


-if you are only using one max7219, then use the function maxSingle to control
 the little guy ---maxSingle(register (1-8), collum (0-255))

-if you are using more then one max7219, and they all should work the same,
then use the function maxAll ---maxAll(register (1-8), collum (0-255))

-if you are using more than one max7219 and just want to change something
at one little guy, then use the function maxOne
---maxOne(Max you wane controll (1== the first one), register (1-8),
collum (0-255))
*********************** DJANDCO*************************
24/04/12

modified the code slightly to allow for Mad Eyes, selects an eye layout
at random and has a random time between changes.

*********************************************************

/* During initiation, be sure to send every part to every max7219 and then
 upload it.
For example, if you have five max7219's, you have to send the scanLimit 5 times
before you load it-- other wise not every max7219 will get the data. the
function maxInUse  keeps track of this, just tell it how many max7219 you are
using.
*/
#include <math.h>

int dataIn = 10;
int load = 11;
int clock = 12;
int RandDelay;
int action;

int maxInUse = 1;    //change this variable to set how many MAX7219's you'll use

int e = 0;       // just a varialble

         // define max7219 registers
byte max7219_reg_noop   = 0x00;
byte max7219_reg_digit0 = 0x01;
byte max7219_reg_digit1 = 0x02;
byte max7219_reg_digit2 = 0x03;
byte max7219_reg_digit3 = 0x04;
byte max7219_reg_digit4 = 0x05;
byte max7219_reg_digit5 = 0x06;
byte max7219_reg_digit6 = 0x07;
byte max7219_reg_digit7 = 0x08;
byte max7219_reg_decodeMode  = 0x09;
byte max7219_reg_intensity   = 0x0a;
byte max7219_reg_scanLimit   = 0x0b;
byte max7219_reg_shutdown    = 0x0c;
byte max7219_reg_displayTest = 0x0f;

void putByte(byte data) {
  byte i = 8;
  byte mask;
  while(i > 0) {
    mask = 0x01 << (i - 1); // get bitmask
    digitalWrite( clock, LOW);   // tick
    if (data & mask){   // choose bit
  digitalWrite(dataIn, HIGH);// send 1
    }else{
  digitalWrite(dataIn, LOW); // send 0
    }
    digitalWrite(clock, HIGH);   // tock
    --i;         // move to lesser bit
  }
}

void maxSingle( byte reg, byte col) {
//maxSingle is the "easy"  function to use for a     //single max7219

  digitalWrite(load, LOW);   // begin
  putByte(1);     // specify register
  putByte(255);//((data & 0x01) * 256) + data >> 1); // put data
  digitalWrite(load, LOW);   // and load da nuts
  digitalWrite(load,HIGH);
}

void maxAll (byte reg, byte col) {    // initialize  all  MAX7219's in the system
  int c = 0;
  digitalWrite(load, LOW);  // begin
  for ( c =1; c<= maxInUse; c++) {
  putByte(reg);  // specify register
  putByte(col);//((data & 0x01) * 256) + data >> 1); // put data
    }
  digitalWrite(load, LOW);
  digitalWrite(load,HIGH);

}

const int pir = 7;
int start = 0;

void setup () {
  pinMode(pir, INPUT);
  pinMode(dataIn, OUTPUT);
  pinMode(clock,  OUTPUT);
  pinMode(load,   OUTPUT);

//initiation of the max 7219
  maxAll(max7219_reg_scanLimit, 0x07);
  maxAll(max7219_reg_decodeMode, 0x00);  // using an led matrix (not digits)
  maxAll(max7219_reg_shutdown, 0x01);    // not in shutdown mode
  maxAll(max7219_reg_displayTest, 0x00); // no display test
   for (e=1; e<=8; e++) {    // empty registers, turn all LEDs off
    maxAll(e,0);
  }
  maxAll(max7219_reg_intensity, 0x0f & 0x0f);    // the first 0x0f is the value you can set
                  // range: 0x00 to 0x0f
}

//int state = 0;

void loop () {
  if(digitalRead(pir) == true){
  start = true;  
  }
  while (start) {
    randomAction();
  }
/*
  if(sensorIsTriggered() == true) {
    speakEye();
    randomAction();
  } else {}
*/  

/*
  if(digitalRead(pir) == HIGH) {
    speakEye();
    randomAction();
  } else {
    randomAction(); 
  }
*/
}

void lookUp(){
  for (int j = 0; j <= 3; j++) {
    moveEye(-1, j);
    delay(50);  
  } 
  delay(1000);
  for (int j = 3; j >= 0; j--) {
    moveEye(-1, j);
    delay(50);  
  }
}

void lookDown(){
  for (int j = 0; j >= -2; j--) {
    moveEye(-1, j);
    delay(50);  
  }
  delay(1000);
  for (int j = -2; j <= 0; j++) {
    moveEye(-1, j);
    delay(50);  
  }
}

void lookLeft(){
  for (int i = -1; i <= 1; i++) {
    moveEye(i, 0);
    delay(50);  
  }
  delay(1000);
  for (int i = 1; i >= -1; i--) {
    moveEye(i, 0);
    delay(50);  
  }
}

void lookRight(){
  for (int i = -1; i >= -3; i--) {
    moveEye(i, 0);
    delay(50);  
  }
  delay(1000);
  for (int i = -3; i <= -1; i++) {
    moveEye(i, 0);
    delay(50);  
  }  
}

void blinkEye() {
  for(int i = 1; i<=8; i++){
    for(int j = 1; j <= 8; j++){
      if(j<=i){
        maxAll(j, 0);
      }  else{
        maxAll(j, 255);
      }
      delay(2);
    } 
  }
  for(int i = 8; i>=1; i--){
    for(int j = 8; j >=1; j--){
      if(i<=j){
        maxAll(j, 255);
      } else{
        maxAll(j, 0);
      }
      delay(2);
    } 
  } 
}

void randomAction() {
  int action = random(5);
  switch(action) {
    case 1:
      lookUp();
    case 2:
      lookDown();
    case 3:
      lookLeft();
    case 4:
      lookRight();
    case 5:
      blinkEye();
  }
}



void angryEye(){
  for (int i=1; i<8; i++ ){
    int black = 255 >> i ; 
    maxAll(i, 255-black);
  } 
}

void moveEye(int x,int y) {
  int eyeStep = 7;
  int ball = eyeStep << (x+3);
  for(int i = 1; i <= 8; i++){ 
    if ( i == 4-y || i == 5-y || i == 6-y ){
      maxAll(i, 255-ball);
    } else{
      maxAll(i, 255); 
    }
  }
}

void speakEye(){
  int x = 0; int y = 0;
  int eyeStep = 3;
  int ball = eyeStep << (x+3);
  for(int i = 1; i <= 8; i++){ 
    if ( i == 4-y || i == 5-y ){
      maxAll(i, 255-ball);
    } else{
      maxAll(i, 255); 
    }
  }
  delay(1000);

  x = -1; y = 1;
  eyeStep = 15;
  ball = eyeStep << (x+3);
  for(int i = 1; i <= 8; i++){ 
    if ( i == 4-y || i == 5-y || i == 6-y || i == 7-y ){
      maxAll(i, 255-ball);
    } else{
      maxAll(i, 255); 
    }
  }
  delay(1000);  
  
}
