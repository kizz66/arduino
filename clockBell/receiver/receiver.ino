#define RPM 3
#define LED_PIN 2

#define OUT_DURATION 200
#define PERIOD_TRANSMITTER_LISTEN 49 // real +1  50

const int len = 14;
unsigned long timerDuration;

bool state = false; // текущее состояние светодиода
int pattern[len] = {1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}; // эталонный массив - маска команды, которую нужно «словить»
int testReg[len] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // тестовый регистр - массив оцифрованных значений с входа приёмника

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(RPM, INPUT);
  digitalWrite(LED_PIN, LOW);
  //  Serial.begin(9600);
}

void loop() {
  readReceiver();
  checkOutDuration();
  delay(PERIOD_TRANSMITTER_LISTEN);
}

/**
    readd receiver data
*/
void readReceiver(void) {
  int data = digitalRead(RPM); // читаем значение на входе приёмника
  ShiftReg(data, testReg); // вдвигаем полученное число в тестовый регистр
  if (IsCommandDetected()) { // проверяем, нет ли в тестовом регистре искомой последовательности
    // state = !state; // если есть, меняем состояние светодиода
    // digitalWrite(LED_PIN, state);
    doAction();
  }
}

/**
   вдвигает в тестовый регистр новое значение
*/
void ShiftReg(int newVal, int *arr) {
  for (int i = 0; i < len; i++) {
    arr[i] = testReg[i + 1]; // смещаем значения в регистре на 1 позицию
  }
  arr[len - 1] = newVal; // последнюю позицию заменяем только что принятым измерением
}

/**
   проверяет, обнаружена ли команда на входе приёмника
*/
bool IsCommandDetected() {
  for (int i = 0; i < len; i++) {
    if (testReg[i] != pattern[i]) { // почленно сравниваем 2 массива
      return false;
    }
  }
  return true;
}

/**

*/
void doAction(void) {
  timerDuration = millis();
  state = true;
  digitalWrite(LED_PIN, state);
}

/**

*/
void checkOutDuration(void) {
  if (state && (millis() - timerDuration > OUT_DURATION)) {
    timerDuration = millis();
    state = false;
    digitalWrite(LED_PIN, state);
  }
}
