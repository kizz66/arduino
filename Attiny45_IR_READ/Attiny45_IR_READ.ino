/*
   tiny_IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
   An IR detector/demodulator must be connected to the input RECV_PIN.
   Version 0.1 July, 2009
   Copyright 2009 Ken Shirriff
   http://arcfn.com
*/

#include <tiny_IRremote.h>
#include <EEPROM.h>
const int
RECV_PIN = 3,
LED_PIN = 4;

IRrecv irrecv(RECV_PIN);
decode_results results;
void setup()
{
  digitalWrite(LED_PIN, HIGH);
  irrecv.enableIRIn();
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  if (irrecv.decode(&results)) {
    digitalWrite(LED_PIN, LOW);
    EEPROM.write(0, results.value);
    irrecv.resume();
  }
  delay(1000);
}
