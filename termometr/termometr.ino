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
uint8_t arrowUp[8] = {
  B00100,
  B01110,
  B11111,
  B00100,
  B00100,
  B00100,
  B00100
};
uint8_t arrowDown[8] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B11111,
  B01110,
  B00100
};

float oldHum, oldTemp;
bool isFirstLoop = true;

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
  lcd.createChar(1, arrowUp);
  lcd.createChar(2, arrowDown);


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
    render(h, t - 2.5);
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

  if (isFirstLoop) {
    oldHum = h;
    oldTemp = t;
    isFirstLoop = false;
  } else {
    if (h < oldHum) {
      lcd.setCursor(14, 0);
      lcd.write(1);
    } else if (h > oldHum) {
      lcd.setCursor(14, 0);
      lcd.write(2);
    }

    if (h < oldHum) {
      lcd.setCursor(14, 1);
      lcd.write(1);
    } else if (h > oldHum) {
      lcd.setCursor(14, 1);
      lcd.write(2);
    }
  }
}

