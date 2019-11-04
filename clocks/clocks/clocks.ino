#include "RTClib.h"
#include <IRremote.h>

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

#define IR_INPUT_PIN 3
IRrecv irrecv(IR_INPUT_PIN);
decode_results results;

#define KEY_OK D7E84B1B
#define KEY_UP
#define KEY_DOWN
#define KEY_RIGHT
#define KEY_LEFT
#define KEY_1
#define KEY_2
#define KEY_3
#define KEY_4
#define KEY_5
#define KEY_6
#define KEY_7
#define KEY_8
#define KEY_9
#define KEY_0
#define KEY_STAR
#define KEY_GRILL

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
  pinMode(IR_INPUT_PIN, INPUT);
  
  secondsFlash = LOW;

  irrecv.enableIRIn(); // Start the receiver
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
