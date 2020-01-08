#define LED_PIN_1 1
#define LED_PIN_2 2
#define LED_PIN_3 0

#define KEY_UP 3
#define KEY_DOWN 4

int level = true;
void setup() {
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);

  pinMode(KEY_UP, INPUT);
  pinMode(KEY_DOWN, INPUT);

  digitalWrite(LED_PIN_1, HIGH);
  delay(500);
  digitalWrite(LED_PIN_2, HIGH);
  delay(500);
  digitalWrite(LED_PIN_3, HIGH);
  delay(1000);
  digitalWrite(LED_PIN_1, LOW);
  digitalWrite(LED_PIN_3, LOW);
}

void loop() {
  int up = !digitalRead(KEY_UP);
  int down = !digitalRead(KEY_DOWN);

  if (up) {
    digitalWrite(LED_PIN_3, HIGH);
    digitalWrite(LED_PIN_2, LOW);
  } else {
    digitalWrite(LED_PIN_3, LOW);
  }
  if (down) {
    digitalWrite(LED_PIN_1, HIGH);
    digitalWrite(LED_PIN_2, LOW);
  } else {
    digitalWrite(LED_PIN_1, LOW);
  }
  if (!up && !down) {
    digitalWrite(LED_PIN_2, HIGH);
  }
  
  if (up && down) {
    level = !level;
    digitalWrite(LED_PIN_2, level);
  }

  delay(50);
}
