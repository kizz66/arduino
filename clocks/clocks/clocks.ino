/*
*/

#define DEC_HOURS 8
#define HOURS 7 //ок
#define DEC_MIN 9 // ok
#define MIN 6

#define D1 10
#define D2 12 // ok
#define D3 11 // ок
#define D4 13 // ok

// десятки часов, часы, десятки минут, минуты
int displayData[4] = {1, 2, 3, 4};
int displayDigit[4] = {DEC_HOURS, HOURS, DEC_MIN, MIN};

int chars[10][4] = {
  {LOW, LOW, LOW, LOW},
  {LOW, LOW, LOW, HIGH},
  {LOW, LOW, HIGH, LOW},
  {LOW, LOW, HIGH, HIGH},
  {LOW, HIGH, LOW, LOW},
  {LOW, HIGH, LOW, HIGH},
  {LOW, HIGH, HIGH, LOW},
  {LOW, HIGH, HIGH, HIGH},
  {HIGH, LOW, LOW, LOW},
  {HIGH, LOW, LOW, HIGH},
};

void setValueToDigit(int value, int digitNumber) {
  digitsOff();
  delay(2);
  digitalWrite(D1, chars[value][3]);
  digitalWrite(D2, chars[value][2]);
  digitalWrite(D3, chars[value][1]);
  digitalWrite(D4, chars[value][0]);
  digitalWrite(digitNumber, HIGH);
  delay(3);
}

void digitsOff(void) {
  digitalWrite(DEC_HOURS, LOW);
  digitalWrite(HOURS, LOW);
  digitalWrite(DEC_MIN, LOW);
  digitalWrite(MIN, LOW);
}

void setup() {
  pinMode(DEC_HOURS, OUTPUT);
  pinMode(HOURS, OUTPUT);
  pinMode(DEC_MIN, OUTPUT);
  pinMode(MIN, OUTPUT);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
}

void loop() {
  setValueToDigit(displayData[0], displayDigit[0]);
  setValueToDigit(displayData[1], displayDigit[1]);
  setValueToDigit(displayData[2], displayDigit[2]);
  setValueToDigit(displayData[3], displayDigit[3]);
}
