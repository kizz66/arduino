#include "IRremote.h"
#include <EEPROM.h>

IRrecv irrecv(11); // указываем вывод, к которому подключен приемник
decode_results results;

//Заточена под пульт телевизора LG
int const
OUT_PIN = 3;
int trigger = false;

void setup() {
  bool state = EEPROM.read(0);

  irrecv.enableIRIn(); // запускаем прием
  pinMode(OUT_PIN, OUTPUT);
  pinMode(13, OUTPUT);

  if ( state == 255 ) {
    digitalWrite(OUT_PIN, LOW);// управляем длоком реле (низкий уровень)
    trigger = true;
  } else {
    trigger = false;
    digitalWrite(OUT_PIN, HIGH);
  }
}
void loop() {
  if ( irrecv.decode( &results )) { // если данные пришли
    switch (results.value) {
      case 0xd5257fdb: // RED

        break;
      case 0x80a24e43: // GREEN

        break;
      case 0xf3c645b: // YELLOW
        turnOff();
        break;
      case 0x1fd3b9bf: // BLUE
        turnOn();
    }
    irrecv.resume(); // принимаем следующую команду
  }
  delay(50);
}

void turnOn() {
  if (trigger) return;
  trigger = true;
  digitalWrite(OUT_PIN, LOW);
  digitalWrite(13, HIGH);
  EEPROM.write(0, 255);
}

void turnOff() {
  if (!trigger) return;
  trigger = false;
  digitalWrite(OUT_PIN, HIGH);
  digitalWrite(13, LOW);
  EEPROM.write(0, 0);
}
