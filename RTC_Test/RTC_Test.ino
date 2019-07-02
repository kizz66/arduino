// функции даты и времени с использованием часов реального времени DS1307, подключенные по I2C. В скетче используется библиотека Wire lib

#include <Wire.h>

#include "RTClib.h"

RTC_DS1307 RTC;

void setup () {

Serial.begin(57600);

Wire.begin();

RTC.begin();

if (! RTC.isrunning()) {

Serial.println("RTC is NOT running!");

// строка ниже используется для настройки даты и времени часов

 //RTC.adjust(DateTime(__DATE__, __TIME__));

}

}

void loop () {

DateTime now = RTC.now();

Serial.print(now.year(), DEC);

Serial.print('/');

Serial.print(now.month(), DEC);

Serial.print('/');

Serial.print(now.day(), DEC);

Serial.print(' ');

Serial.print(now.hour(), DEC);

Serial.print(':');

Serial.print(now.minute(), DEC);

Serial.print(':');

Serial.print(now.second(), DEC);

Serial.println();

Serial.print(" since 1970 = ");

Serial.print(now.unixtime());

Serial.print("s = ");

Serial.print(now.unixtime() / 86400L);

Serial.println("d");

// рассчитываем дату: 7 дней и 30 секунд

DateTime future (now.unixtime() + 7 * 86400L + 30);

Serial.print(" now + 7d + 30s: ");

Serial.print(future.year(), DEC);

Serial.print('/');

Serial.print(future.month(), DEC);

Serial.print('/');

Serial.print(future.day(), DEC);

Serial.print(' ');

Serial.print(future.hour(), DEC);

Serial.print(':');

Serial.print(future.minute(), DEC);

Serial.print(':');

Serial.print(future.second(), DEC);

Serial.println();

Serial.println();

delay(3000);

}
