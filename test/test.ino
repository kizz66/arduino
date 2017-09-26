#include <Wire.h>
#include <AnalogButtonTrigger.h>

const int buttonPin = 1;// button read by analog input A2
const int IN1 = 5, IN2 = 4, ENA = 3, JOY_X = 2;

int thorttle = 0;

AnalogButtonTrigger triggerButton = AnalogButtonTrigger(buttonPin);

void setup() {
  Serial.begin (9600);
  pinMode (ENA, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
}

void loop() {
  // Serial.println(triggerButton.check());

  thorttle = map(analogRead(JOY_X), 0, 1023, -255, 255);
    if (thorttle > 0) {
      Serial.println(thorttle);
      analogWrite (IN1, 0);
      digitalWrite (IN2, HIGH);
    } else {
      Serial.println(thorttle);
      analogWrite (IN1, 255);
      digitalWrite (IN2, LOW);
    }
  analogWrite(ENA, abs(thorttle));
  delay(50);
}
