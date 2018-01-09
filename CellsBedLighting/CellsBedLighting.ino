#include "IRremote.h"

IRrecv irrecv(11); // указываем вывод, к которому подключен приемник
decode_results results;

//Заточена под пульт телевизора LG
int const
OUT_PIN = 9;
bool state = true;
void setup() {
  irrecv.enableIRIn(); // запускаем прием
  pinMode(OUT_PIN, OUTPUT);
  pinMode(13, OUTPUT);
}
void loop() {
  if ( irrecv.decode( &results )) { // если данные пришли
    switch (results.value) {
      case 0xd5257fdb: // RED

        break;
      case 0x80a24e43: // GREEN

        break;
      case 0xf3c645b: // YELLOW

        break;
      case 0x1fd3b9bf: // BLUE
        state = !state;
    }
    irrecv.resume(); // принимаем следующую команду
  }
  turn();
  delay(50);
}

void turn() {
  if (state) {
    digitalWrite(OUT_PIN, HIGH);
    digitalWrite(13, LOW);
  } else {
    digitalWrite(OUT_PIN, LOW);
    digitalWrite(13, HIGH);
  }
}
