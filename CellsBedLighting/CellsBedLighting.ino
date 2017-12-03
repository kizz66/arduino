#include "IRremote.h"
#include <Wire.h>

IRrecv irrecv(2); // указываем вывод, к которому подключен приемник

decode_results results;
//Заточена под пульт телевизора LG
String const
RED_KEY     = "20df4eb1",
GREEN_KEY   = "20df8e71",
YELLOW_KEY  = "20dfc639",
BLUE_KEY    = "20df8679",
REPEAT_KEY  = "ffffffff";

String key = "";

int
value = 0,
ratio = 10;

void setup() {
  Serial.begin(9600); // выставляем скорость COM порта
  irrecv.enableIRIn(); // запускаем прием
}

void loop() {

  if ( irrecv.decode( &results )) { // если данные пришли
    String result = String(results.value, HEX);

    if (result != REPEAT_KEY) {
      key = result;
    }
    if (key == RED_KEY) {
   
    } else if (key == GREEN_KEY) {
    
    } else  if (key == YELLOW_KEY) {
      value += ratio;
      value = value <= 255 ? value : 255;
    } else if (key == BLUE_KEY) {
      value -= ratio;
      value = value >= 0 ? value : 0;
    }
    irrecv.resume(); // принимаем следующую команду
    Serial.println(value);
  }
}
