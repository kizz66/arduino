/*
   tiny_IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
   An IR detector/demodulator must be connected to the input RECV_PIN.
   Version 0.1 July, 2009
   Copyright 2009 Ken Shirriff
   http://arcfn.com
*/

#include <tiny_IRremote.h>

const int
RECV_PIN = 0,
LED_PIN = 1;

int button = 0x1FD3B9BF; // синяя кнопка

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);

  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results) && results.value == 0x1fd3b9bf) {
    digitalWrite(LED_PIN, HIGH);
    irrecv.resume(); // Receive the next value
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  delay(50);
}
