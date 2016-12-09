
int stepPin = 2; // pin that controls how much the motor moves
int ledPin = 13; // pin for display

// for stepMotor:
int delayLength = 1; // length of delay in ms
int stepLength = 2; // degrees each step travels

// ISP Capability:
#include <Wire.h>
int I2Caddress = 1; // the arduino's I2C address

void setup() {
  Wire.begin(I2Caddress);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event

  // set pinmode for all pins:
  pinMode(stepPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  delay(10); // delay at 
}

void receiveEvent(int howMany) {
  int x = Wire.read();    // receive byte as an integer
  
  if (x == I2Caddress) { // looks for the arduino's I2C address
    stepMotor();
  }
  
}

void stepMotor() {
  for (int i = 0; i < (360 / stepLength); i++) {
    digitalWrite(stepPin, HIGH);
    digitalWrite(ledPin, HIGH);
    delay(delayLength);
    digitalWrite(stepPin, LOW);
    digitalWrite(ledPin, LOW);
    delay(delayLength);
  }
}

