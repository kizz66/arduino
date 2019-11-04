#include "RTClib.h"
#include <IRremote.h>

RTC_DS1307 RTC;

#define PERIOD_1 500
#define PERIOD_2 1000
#define PERIOD_3 50 /* for ir reading */

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
#define KEY_UP 0x55555555
#define KEY_DOWN 0x55555555
#define KEY_RIGHT 0x55555555
#define KEY_LEFT 0x55555555
#define KEY_1 0x55555555
#define KEY_2 0x55555555
#define KEY_3 0x55555555
#define KEY_4 0x55555555
#define KEY_5 0x55555555
#define KEY_6 0x55555555
#define KEY_7 0x55555555
#define KEY_8 0x55555555
#define KEY_9 0x55555555
#define KEY_0 0x55555555
#define KEY_STAR 0x55555555
#define KEY_GRILL 0x55555555

unsigned long timer_1, timer_2, timer_3;
bool secondsFlash;
bool setTime = false;

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
    if (setTime) {
      secondsFlash = HIGH;
    } else {
      secondsFlash = secondsFlash ? LOW : HIGH;
    }
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

  /**
     500 ms block
     Read IR
  */
  if (millis() - timer_3 > PERIOD_3) {
    timer_3 = millis();
    readIr();
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
/**
  reading IR
*/
void readIr(void) {
  if ( irrecv.decode( &results )) {

    switch (results.value) {
      case 0xD7E84B1B://OK
        setTime = setTime ? false : true;
        break;
      case 0x511DBB://UP
        setTime = setTime ? false : true;
        break;
      case 0xA3C8EDDB://DOWN
        setTime = setTime ? false : true;
        break;
      case 0x20FE4DBB://RIGHT
        setTime = setTime ? false : true;
        break;
      case 0x52A3D41F://LEFT
        setTime = setTime ? false : true;
        break;
      case 0xC101E57B://1
        setTime = setTime ? false : true;
        break;
      case 0x97483BFB://2
        setTime = setTime ? false : true;
        break;
    }
    
    irrecv.resume(); // Receive the next value
  }
}
