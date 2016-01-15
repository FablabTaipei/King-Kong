/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int pir = 7;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(pir, INPUT);
  Serial.begin(9600);
}

int preSensorValue = 0;

void loop() {
  
  int sensorValue = digitalRead(pir);  
  
  
  if (preSensorValue ==0 && sensorValue ==1) {
    digitalWrite(13, HIGH);
    myservo.write(150);
    delay(4000);
  }

  preSensorValue = sensorValue;
  myservo.write(115);
  
}

