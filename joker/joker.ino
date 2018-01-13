const int UP = 0,
          DOWN = 1;

int led = 1, // 3 - UNO
    val,
    valueTriggedLevel = 5 50,
    outValue = 0,
    lightDuration = 5,
    direct = UP;

bool isFlash = false,
     flashTrigger = false;


void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  val = analogRead(2); // A0 - UNO
  if (val > valueTriggedLevel) {
    if ( flashTrigger ) {
      isFlash = true;
      flashTrigger = false;
    }
  } else {
    flashTrigger = true;
  }

  doFlash();
  delay(30);
}

void doFlash(void) {
  if (isFlash) {
    analogWrite(led, outValue);
    if (direct == UP) {
      outValue = outValue+5;
      if (outValue > 255) {
        outValue = 255;
        direct = DOWN;
      }
    } else {
      outValue = outValue - 1;
      if (outValue < 0 ) {
        outValue = 0;
        direct = UP;
        isFlash = false;
      }
    }
  }
}

