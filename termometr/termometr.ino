#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2

//const int movPin = 4;

uint8_t degres[8] = {
  B01110,
  B10001,
  B10001,
  B01110,
  B00000,
  B00000,
  B00000
};

DHT dht(DHTPIN, DHT22);
LiquidCrystal_I2C lcd(0x3f, 16, 2);

void setup() {
  //Serial.begin(9600);

 // pinMode(movPin, INPUT);
  dht.begin();
  lcd.init();
  lcd.createChar(0, degres);
  lcd.backlight();
}

void loop() {
  delay(1200);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Sensor error");
  } else {
    render(h, t);
  }

//  if (digitalRead(movPin)) {
//    lcd.backlight();
//  } else {
//    lcd.noBacklight();
//  }
}

/**

*/
void render(float h, float t) {
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Hum  ");
  lcd.print(h, 0);
  lcd.print(" %");
  lcd.setCursor(1, 1);
  lcd.print("Temp ");
  lcd.print(t, 1);
  lcd.print(" ");
  lcd.write(0);
  lcd.print("C");
}

