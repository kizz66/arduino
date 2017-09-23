#include <Wire.h>
#include <AnalogButtonTrigger.h>

const int ledPin = 13;
const int buttonPin = 2;// button read by analog input

AnalogButtonTrigger triggerButton = AnalogButtonTrigger(buttonPin);

void setup() {
  Serial.begin (9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  Serial.println(triggerButton.check());
  // Serial.println(t);
  // Serial.println(map(t, 0, 1023, -1023, 1023));
  delay(50);
}
