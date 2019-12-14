const int prm = 3; // пин входа приёмника XY-MK-5V
const int ledPin = 2; // пин встроенного светодиода Arduino
const int len = 14; // длина массивов

bool state = false; // текущее состояние светодиода
int pattern[len] = {1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}; // эталонный массив - маска команды, которую нужно «словить»
int testReg[len] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // тестовый регистр - массив оцифрованных значений с входа приёмника

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin, INPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  int data = digitalRead(prm); // читаем значение на входе приёмника
  ShiftReg(data, testReg); // вдвигаем полученное число в тестовый регистр
  if (IsCommandDetected) { // проверяем, нет ли в тестовом регистре искомой последовательности
    state = !state; // если есть, меняем состояние светодиода
    digitalWrite(ledPin, state);
  }
  delay(50);
}

// вдвигает в тестовый регистр новое значение
void ShiftReg(int newVal, int *arr) {
  for (int i = 0; i < len; i++) {
    arr[i] = testReg[i + 1]; // смещаем значения в регистре на 1 позицию
  }
  arr[len - 1] = newVal; // последнюю позицию заменяем только что принятым измерением
}

// проверяет, обнаружена ли команда на входе приёмника
bool IsCommandDetected() {
  for (int i = 0; i < len; i++) {
    if (testReg[i] != pattern[i]) { // почленно сравниваем 2 массива
      return false;
    }
  }
  return true;
}
