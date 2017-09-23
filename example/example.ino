#include <Wire.h>
#include <AnalogButtonTrigger.h>

const int buttonAnalogPin = 2;// button read by analog input

AnalogButtonTrigger triggerButton = AnalogButtonTrigger(buttonAnalogPin);

void setup() {
  Serial.begin (9600);
}

void loop() {
  Serial.println(triggerButton.check());
  delay(50);
}
