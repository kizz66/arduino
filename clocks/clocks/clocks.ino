#include "RTClib.h"

RTC_DS1307 RTC;

#define PERIOD_1 500
#define PERIOD_2 1000

#define DEC_HOURS 8
#define HOURS 7
#define DEC_MIN 9
#define MIN 6

#define D1 10
#define D2 12
#define D3 11
#define D4 13

#define SEC_PIN 2



unsigned long timer_1, timer_2, timer_3;
bool secondsFlash;

// десятки часов, часы, десятки минут, минуты
int8_t displayData[4] = {1, 2, 3, 4};
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

void setup() {
  RTC.begin();
  pinMode(DEC_HOURS, OUTPUT);
  pinMode(HOURS, OUTPUT);
  pinMode(DEC_MIN, OUTPUT);
  pinMode(MIN, OUTPUT);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  pinMode(SEC_PIN, OUTPUT);
  secondsFlash = LOW;

  if (! RTC.isrunning()) {
    // строка ниже используется для настройки даты и времени часов
    // RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}

void loop() {
  /**
     500 ms block
     Seconds flash
  */
  if (millis() - timer_1 > PERIOD_1) {
    timer_1 = millis();

    secondsFlash = secondsFlash ? LOW : HIGH;
    digitalWrite(SEC_PIN, secondsFlash);
  }

  /**
     1000 ms block
     Read clock
  */
  if (millis() - timer_2 > PERIOD_2) {
    timer_2 = millis();

    DateTime now = RTC.now();
    displayData[0] = now.hour() / 10;
    displayData[1] = now.hour() % 10;
    displayData[2] = now.minute() / 10;
    displayData[3] = now.minute() % 10;
  }

  setValueToDigit(displayData[0], displayDigit[0]);
  setValueToDigit(displayData[1], displayDigit[1]);
  setValueToDigit(displayData[2], displayDigit[2]);
  setValueToDigit(displayData[3], displayDigit[3]);
}
/**

*/
void setValueToDigit(int value, int digitNumber) {
  digitsOff();
  delay(2);
  digitalWrite(D1, chars[value][3]);
  digitalWrite(D2, chars[value][2]);
  digitalWrite(D3, chars[value][1]);
  digitalWrite(D4, chars[value][0]);
  digitalWrite(digitNumber, HIGH);
  delay(2);
}
/**

*/
void digitsOff(void) {
  digitalWrite(DEC_HOURS, LOW);
  digitalWrite(HOURS, LOW);
  digitalWrite(DEC_MIN, LOW);
  digitalWrite(MIN, LOW);
}
