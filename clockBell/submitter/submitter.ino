/*

*/
#define LED_PIN 3
#define SUBMITTER_PIN 4
#define CONTROL_PIN 1

#define DELAY 10
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
  delay(50);
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
  delay(DELAY * 2);
  digitalWrite(SUBMITTER_PIN, LOW);
  delay(DELAY);
  digitalWrite(SUBMITTER_PIN, HIGH);
  delay(DELAY);
  digitalWrite(SUBMITTER_PIN, LOW);
  delay(DELAY);
  digitalWrite(SUBMITTER_PIN, HIGH);
  delay(DELAY * 2);
  digitalWrite(SUBMITTER_PIN, LOW);
  delay(DELAY);
  digitalWrite(LED_PIN, LOW);
}
