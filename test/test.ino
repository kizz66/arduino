#include <Wire.h>
const int ledPin = 13;
const int pin = 8;
void setup() {
  Serial.begin (9600);
  pinMode(ledPin, OUTPUT);
  pinMode(pin, INPUT);
  digitalWrite(pin,HIGH);
}

void loop() {
  Serial.println(map(analogRead(2),0,1023,-1023,1023));  
  delay(50);
}
