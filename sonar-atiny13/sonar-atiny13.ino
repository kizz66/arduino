const int SONAR_ACTIVED_LED = 1,
          LAMP_LED = 0,
          SONAR_TRIGGER = 3,
          SONAR_ECHO = 4,
          ON_SPEED = 20,
          OFF_SPEED = 5;


int offDelayTicks = 20,
    ticks = 0,
    lampValue = 0;
bool lampOn = false;

void setup() {
  pinMode(SONAR_ACTIVED_LED, OUTPUT);
  pinMode(LAMP_LED, OUTPUT);
  pinMode(SONAR_TRIGGER, OUTPUT);
  pinMode(SONAR_ECHO, INPUT);
  startTest();
}

void loop() {
  int duration = 0, cm = 0;
  digitalWrite(SONAR_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(SONAR_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(SONAR_TRIGGER, LOW);
  duration = pulseIn(SONAR_ECHO, HIGH, 100000);
  cm = duration / 58;

  if (cm > 0 && cm < 150) {
    digitalWrite(SONAR_ACTIVED_LED, HIGH);
  } else {
    digitalWrite(SONAR_ACTIVED_LED, LOW);
  }

  if (cm > 0 && cm < 60) {
    lampOn = true;
    ticks = 0;
  } else {
    ticks++;
    lampOn = false;
  }
  checkLamp();
  delay(5);
}

void checkLamp(void) {
  if (lampOn) {
    turnLampOn();
  } else if (ticks >= offDelayTicks) {
    ticks = 0;
    turnLampOff();
  }
}

void turnLampOn() {
  lampValue += ON_SPEED;
  lampValue = (lampValue > 255) ? 255 : lampValue;
  analogWrite(LAMP_LED, lampValue);
}

void turnLampOff() {
  lampValue = lampValue - OFF_SPEED;
  lampValue = (lampValue <= 0) ? 0 : lampValue;
  analogWrite(LAMP_LED, lampValue);
}

void startTest(void) {
  digitalWrite(LAMP_LED, LOW);
  delay(1000);
  digitalWrite(SONAR_ACTIVED_LED, HIGH);
  delay(200);
  digitalWrite(SONAR_ACTIVED_LED, LOW);
  delay(500);
  digitalWrite(SONAR_ACTIVED_LED, HIGH);
  delay(200);
  digitalWrite(SONAR_ACTIVED_LED, LOW);
  delay(500);
}

