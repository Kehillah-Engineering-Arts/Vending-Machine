
// ISP Capability:
#include <Wire.h>
int ledPin = 13;
int readerPin = 2;

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)

  pinMode(ledPin, OUTPUT);
  pinMode(readerPin, INPUT);
}

void loop() {
  if (digitalRead(readerPin) == 1) {
    transmitData();
  }
  delay(10);
}

void transmitData() {
  digitalWrite(ledPin, HIGH); // signal transmission
  Wire.beginTransmission(1); // transmit to device #8
  Wire.write(1);              // sends one byte (the I2C address for the first stepper motor)
  Wire.endTransmission();    // stop transmitting
  digitalWrite(ledPin, LOW); // signal transmission
}

