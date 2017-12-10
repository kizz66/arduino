#include "IRremote.h"

IRrecv irrecv(11); // указываем вывод, к которому подключен приемник

decode_results results;
//Заточена под пульт телевизора LG
int const
ANALOG_OUT_PIN = 3;

int out = 0;

void setup() {
  irrecv.enableIRIn(); // запускаем прием
  pinMode(ANALOG_OUT_PIN, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {

  if ( irrecv.decode( &results )) { // если данные пришли
    switch (results.value) {
      case 0xd5257fdb:
        digitalWrite(13, LOW);
        analogWrite(ANALOG_OUT_PIN, 0);
        break;
      case 0x80a24e43:
        digitalWrite(13, LOW);
        analogWrite(ANALOG_OUT_PIN, 150);
        break;
      case 0xf3c645b:
        digitalWrite(13, LOW);
        analogWrite(ANALOG_OUT_PIN, 200);
        break;
      case 0x1fd3b9bf:
        analogWrite(ANALOG_OUT_PIN, 255);
        digitalWrite(13, HIGH);
    }
    irrecv.resume(); // принимаем следующую команду
  }
}
