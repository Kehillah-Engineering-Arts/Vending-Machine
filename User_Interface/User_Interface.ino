
#include <Wire.h>
/*
 *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  * * * * * * * * * * * * * * * * * * * VARIABLES * * * * * * * * * * * * * * * * * * *
 *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
 
      // inputs:
      int upButton = 2;
      int downButton = 3;
      int leftButton = 4;
      int rightButton = 5;
      int centerButton = 6;
      
      int delayLength = 500; // delay after button push
      
      // led outputs:
      int ledA = 7;
      int ledB = 8;
      int ledC = 9;
      int led1 = 10;
      int led2 = 11;
      int led3 = 12;
      int led4 = 13;
      
      int xVals[] = {ledA, ledB, ledC};
      int yVals[] = {led1, led2, led3, led4};
      
      int x; // x-position of current light
      int y; // y-position of current light
      
      // transmission:
      int dev1 = 8; // Device #1's I2C address
      int dev2 = 7; // Device #2's I2C address
      
      int devices[] = {dev1, dev2};

/*
 *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  * * * * * * * * * * * * * * * * * * * MAIN LOOP * * * * * * * * * * * * * * * * * * *
 *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
 
      void setup() {
        Serial.begin(9600);
        Wire.begin(); // join i2c bus (address optional for master)
      
        // set up pins:
        pinMode(upButton, INPUT);
        pinMode(downButton, INPUT);
        pinMode(leftButton, INPUT);
        pinMode(rightButton, INPUT);
        pinMode(centerButton, INPUT);
        pinMode(ledA, OUTPUT);
        pinMode(ledB, OUTPUT);
        pinMode(ledC, OUTPUT);
        pinMode(led1, OUTPUT);
        pinMode(led2, OUTPUT);
        pinMode(led3, OUTPUT);
        pinMode(led4, OUTPUT);
      
        // starting selected values:
        x = 0;
        y = 0;
      }
      
      void loop() {
        if (digitalRead(upButton) == HIGH) {
          Serial.println("up");
          scrollUp();
        }
        else if (digitalRead(downButton) == HIGH) {
          Serial.println("down");
          scrollDown();
        }
        else if (digitalRead(rightButton) == HIGH) {
          Serial.println("right");
          scrollRight();
        }
        else if (digitalRead(leftButton) == HIGH) {
          Serial.println("left");
          scrollLeft();
        }
        else if (digitalRead(centerButton) == HIGH) {
          Serial.println("select");
          transmitSelection();
        }
        delay(10); // limit CPU consumption
      }

/*
 *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  * * * * * * * * * * * * * FUNCTIONS FOR BUTTONS AND LIGHTS  * * * * * * * * * * * * *
 *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
 
      void scrollUp() { // decrease the y-value by one
        y -= 1;
        while (y < 0) {
          y += 4;
        }
        y %= 4;
        turnOffLights();
        turnOnLight(x, y);
        delay(delayLength - 10);
      }
      
      void scrollDown() { // increase the y-value by one
        y += 1;
        y %= 4;
        turnOffLights();
        turnOnLight(x, y);
        delay(delayLength - 10);
      }
      
      void scrollLeft() { // decrease the x-value by one
        x -= 1;
        while (x < 0) {
          x += 3;
        }
        x %= 3;
        turnOffLights();
        turnOnLight(x, y);
        delay(delayLength - 10);
      }
      
      void scrollRight() { // increase the y-value by one
        x += 1;
        x %= 3;
        turnOffLights();
        turnOnLight(x, y);
        delay(delayLength - 10);
      }
      
      void transmitSelection() {
        for (int d = 0; d < sizeof(devices); d++) {
          Wire.beginTransmission(devices[d]); // transmit to the device
          Wire.write(x + y * 3);    // sends one byte
          Serial.print(d);
          Serial.print(": ");
          Serial.println(x + y * 3);
          Wire.endTransmission();    // stop transmitting
        }
        delay(delayLength - 10);
      }
      
      void turnOffLights() {
        for (int i = 0; i < sizeof(xVals); i++) {
          digitalWrite(xVals[i], LOW);
        }
        for (int i = 0; i < sizeof(yVals); i++) {
          digitalWrite(yVals[i], LOW);
        }
      }
      
      void turnOnLight(int xVal, int yVal) {
        digitalWrite(xVals[xVal], HIGH);
        digitalWrite(yVals[yVal], HIGH);
        Serial.print(xVals[xVal]);
        Serial.print(": ");
        Serial.println(yVals[yVal]);
      }
