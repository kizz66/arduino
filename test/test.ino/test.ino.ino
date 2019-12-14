#define RES_PIN A0

void setup() {
  Serial.begin(9600);
  pinMode(RES_PIN, INPUT);
}

void loop() {
  int data = digitalRead(RES_PIN);
  Serial.println(data);
  delay(50);
}
