#include <Wire.h>
#include <SPI.h> // Подключаем библиотеку  для работы с шиной SPI
#include <Encoder.h>
#include <MapEncoder.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); // Устанавливаем дисплей 0x27 или 0х3F

const int ledPin = 13;

const int encoderButton = 2;
const int CLK_PIN = 3;
const int DT_PIN = 4;

long oldPosition  = 0;
MapEncoder encoder(DT_PIN, CLK_PIN, encoderButton);

void setup() {
  pinMode(ledPin, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initialize");
  encoder.setScale(45, 135, 90, 1);
}

void loop() {
  long newPosition = encoder.getValue();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(oldPosition);
  }
}
