#include "DHT.h"
#include <Thread.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2

const int movPin = 4;

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
Thread tempThread = Thread();
Thread moveThread = Thread();

void setup() {
  //Serial.begin(9600);
  pinMode(movPin, INPUT);
  dht.begin();
  lcd.init();
  lcd.createChar(0, degres);

  tempThread.onRun(handleReadTemp);
  tempThread.setInterval(10000);
  moveThread.onRun(handleReadMove);
  moveThread.setInterval(500);
  lcd.backlight();
  handleReadTemp();
}

void loop() {
  delay(50);
  if (tempThread.shouldRun())tempThread.run();
  if (moveThread.shouldRun())moveThread.run();
}

/**
   Датчик движения
*/
void handleReadMove(void) {
  if (digitalRead(movPin)) {
    lcd.backlight();
  } else {
    lcd.noBacklight();
  }
}

/**
   Датчик температуры
*/
void handleReadTemp(void) {

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    lcd.setCursor(15, 0);
    lcd.print("E");
  } else {
    render(h, t);
  }
}
/**

*/
void render(float h, float t) {
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

