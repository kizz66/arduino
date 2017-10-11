#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2

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
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.createChar(0, degres);
}

void loop() {
  delay(2000);
  float h = 23; // dht.readHumidity();
  float t = 26;//dht.readTemperature();

  //  if (isnan(h) || isnan(t)) {
  //    Serial.println("Не удается считать показания");
  //    return;
  //  }

  render(h, t);
  // lcd.noBacklight();
}

/**

*/
void render(float h, float t) {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Humidity: ");
  lcd.print(h, 0);
  lcd.print(" %");
  lcd.setCursor(1, 1);
  lcd.print("Temperature: ");
  lcd.print(t, 1);
  lcd.print(" ");
  lcd.write(0);
}

