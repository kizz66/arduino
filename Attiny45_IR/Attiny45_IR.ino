/*
   tiny_IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
   An IR detector/demodulator must be connected to the input RECV_PIN.
   Version 0.1 July, 2009
   Copyright 2009 Ken Shirriff
   http://arcfn.com
*/

#include <tiny_IRremote.h>
#include <TinyWireS.h>
const int
RECV_PIN = 3,
LED_PIN = 4;

int code;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.value == 0x20DF8877 ) {
      digitalWrite(LED_PIN, LOW);
    } else {
      digitalWrite(LED_PIN, HIGH);
    }
    irrecv.resume(); // Receive the next value
  }
}
