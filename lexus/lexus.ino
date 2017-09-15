#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>                                          // Подключаем библиотеку  для работы с шиной SPI
#include <nRF24L01.h>                                     // Подключаем файл настроек из библиотеки RF24
#include <RF24.h>                                         // Подключаем библиотеку  для работы с nRF24L01+


Servo servo1;
const int pinServo = 8; // пин для подключения сервопривода
LiquidCrystal_I2C lcd(0x3F, 16, 2); // Устанавливаем дисплей 0x27 или 0х3F

int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
  servo1.attach(pinServo);

  lcd.init();
  lcd.backlight();
}

void loop() {
  int t2 = map(analogRead (0), 0, 1023, 0, 180);
  lcd.clear();
  lcd.setCursor(4, 1);
  lcd.print("------");
  lcd.setCursor(0, 0);
  lcd.print(t2);
  servo1.write(t2); // поворот сервоприводов на полученный угол
  delay(10);

  //  digitalWrite(ledPin, HIGH);
  //  delay(50);
  //  digitalWrite(ledPin, LOW);
  //  delay(1000);
}
