#include "RTClib.h"
#include <IRremote.h>

RTC_DS1307 RTC;

#define PERIOD_1 500 /* for seconds flashing */
#define PERIOD_2 1000 /* for clock reading */
#define PERIOD_3 50 /* for ir reading */
#define PERIOD_4 300 /* for digit blinking */

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

unsigned long timer_1, timer_2, timer_3, timer_4;
bool secondsFlash;
bool setTime = false;
bool digitBlink = false;

// десятки часов, часы, десятки минут, минуты
int8_t displayData[4] = {1, 2, 3, 4};
int displayDigit[4] = {DEC_HOURS, HOURS, DEC_MIN, MIN};

int currentDigitToSetup = 0; // 0-3

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
     Seconds flash
  */
  if (millis() - timer_1 > PERIOD_1) {
    timer_1 = millis();
    if (setTime) {
      secondsFlash = HIGH;
    } else {
      secondsFlash = secondsFlash ? LOW : HIGH;
    }
    digitalWrite(SEC_PIN, secondsFlash);
  }

  /**
     Read clock
  */
  if (millis() - timer_2 > PERIOD_2) {
    timer_2 = millis();

    if (!setTime) {
      DateTime now = RTC.now();
      displayData[0] = now.hour() / 10;
      displayData[1] = now.hour() % 10;
      displayData[2] = now.minute() / 10;
      displayData[3] = now.minute() % 10;
    }
  }

  /**
     Read IR
  */
  if (millis() - timer_3 > PERIOD_3) {
    timer_3 = millis();
    readIr();
  }
  /**
    digit blinking
  */
  if (millis() - timer_4 > PERIOD_4) {
    timer_4 = millis();
    digitBlink = digitBlink ? false : true;
  }

  if (!setTime) {
    setValueToDigit(displayData[0], displayDigit[0], true);
    setValueToDigit(displayData[1], displayDigit[1], true);
    setValueToDigit(displayData[2], displayDigit[2], true);
    setValueToDigit(displayData[3], displayDigit[3], true);
  } else {
    // установка времени мигание текущего разряда
    setValueToDigit(displayData[0], displayDigit[0], currentDigitToSetup == 0 ? digitBlink : true);
    setValueToDigit(displayData[1], displayDigit[1], currentDigitToSetup == 1 ? digitBlink : true);
    setValueToDigit(displayData[2], displayDigit[2], currentDigitToSetup == 2 ? digitBlink : true);
    setValueToDigit(displayData[3], displayDigit[3], currentDigitToSetup == 3 ? digitBlink : true);
  }
}
/**

*/
void setValueToDigit(int value, int digitNumber, bool blink) {
  digitsOff();
  delay(2);
  digitalWrite(D1, chars[value][3]);
  digitalWrite(D2, chars[value][2]);
  digitalWrite(D3, chars[value][1]);
  digitalWrite(D4, chars[value][0]);
  if (blink) {
    digitalWrite(digitNumber, HIGH);
  }
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
/*
  Turn time setup mode to ON
*/
void setTimeOn(void) {
  setTime = true;
  digitsOff();
}
/*
  Turn time setup mode to OFF
*/
void setTimeOff(void) {

  RTC.adjust(DateTime(2019, 1, 1, displayData[0] * 10 + displayData[1], displayData[2] * 10 + displayData[3], 0));
  setTime = false;
}
/*

*/
int getDigitLimit(void) {
  switch (currentDigitToSetup) {
    case 0:
      return 2;
    case 1:
      return 4;
    case 2:
      return 5;
    case 3:
      return 9;
  }
}
/*

*/
void digitIncrease(void) {
  int value = displayData[currentDigitToSetup];
  int limit = getDigitLimit();
  value++;
  value = value > limit ? 0 : value;
  displayData[currentDigitToSetup] = value;
}
/*

*/
void digitDecrease(void) {
  int value = displayData[currentDigitToSetup];
  int limit = getDigitLimit();
  value--;
  value = value < 0 ? limit : value;
  displayData[currentDigitToSetup] = value;
}
/**
  reading IR
*/
void readIr(void) {
  if ( irrecv.decode( &results )) {

    switch (results.value) {
      case 0xD7E84B1B://OK
        if (setTime) {
          setTimeOff();
        } else {
          setTimeOn();
        }
        break;
      case 0x511DBB://UP
        digitIncrease();
        break;
      case 0xA3C8EDDB://DOWN
        digitDecrease();
        break;
      case 0x20FE4DBB://RIGHT
        currentDigitToSetup++;
        currentDigitToSetup = currentDigitToSetup > 3 ? 0 : currentDigitToSetup;
        break;
      case 0x52A3D41F://LEFT
        currentDigitToSetup--;
        currentDigitToSetup = currentDigitToSetup < 0 ? 3 : currentDigitToSetup;
        break;
    }

    irrecv.resume(); // Receive the next value
  }
}
