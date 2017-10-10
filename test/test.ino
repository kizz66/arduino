#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
DHT dht(DHTPIN, DHT22);
LiquidCrystal_I2C lcd(0x3f, 16, 2);

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.print("iarduino.ru");
  lcd.setCursor(8, 1);
  lcd.print("LCD 1602");
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Не удается считать показания");
    return;
  }

  Serial.print(" Влажность:%\t");
  Serial.print(h);
  Serial.print(" Температура:\t");
  Serial.print(t);
  Serial.print("C \n");
}

