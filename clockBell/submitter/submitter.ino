/*

*/
#define LED_PIN 3
#define SUBMITTER_PIN 4
#define CONTROL_PIN 1

int oldControlValue = LOW;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(SUBMITTER_PIN, OUTPUT);
  pinMode(CONTROL_PIN, INPUT);
}

/**

*/
void loop() {
  if (checkInputControl(digitalRead(CONTROL_PIN))) {
    submit();
  }
  delay(200);
}

/**

*/
bool checkInputControl(int value) {
  if (value == HIGH && oldControlValue == LOW) {
    oldControlValue = HIGH;
    return true;
  }
  if (value == LOW && oldControlValue == HIGH) {
    oldControlValue = LOW;
  }
  return false;
}

/**

*/
void submit() {
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(SUBMITTER_PIN, HIGH);
  delay(100);
  digitalWrite(SUBMITTER_PIN, LOW);
  delay(50);
  digitalWrite(SUBMITTER_PIN, HIGH);
  delay(50);
  digitalWrite(SUBMITTER_PIN, LOW);
  delay(50);
  digitalWrite(SUBMITTER_PIN, HIGH);
  delay(100);
  digitalWrite(SUBMITTER_PIN, LOW);
  delay(50);
  digitalWrite(LED_PIN, LOW);
}
