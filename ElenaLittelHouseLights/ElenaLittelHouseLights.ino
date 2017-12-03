const int R_PIN = 0;
const int B_PIN = 1;

int Rval = 0, Bval = 0;

void fadeIn(int Rmax, int Bmax, int fadeAmount = 1, int delayTime = 30)
{
  for (int i = 0; i <= 255; i += fadeAmount) {
    Rval += fadeAmount;
    Bval += fadeAmount;
    Rval = Rval <= Rmax ? Rval : Rmax;
    Bval = Bval <= Bmax ? Bval : Bmax;
    analogWrite(R_PIN, Rval );
    analogWrite(B_PIN, Bval);
    delay(delayTime);
  }
}

void fadeOut(int Rmin, int Bmin, int fadeAmount = 1, int delayTime = 30)
{
  for (int i = 255; i >= 0; i -= fadeAmount) {
    Rval -= fadeAmount;
    Bval -= fadeAmount;
    Rval = Rval >= Rmin ? Rval : Rmin;
    Bval = Bval >= Bmin ? Bval : Bmin;
    analogWrite(R_PIN, Rval );
    analogWrite(B_PIN, Bval);
    delay(delayTime);
  }
}

void setup() {
  pinMode(R_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
}

void loop() {
  fadeIn(255, 255);

//  for (int i = 0; i <= 10; i++) {
//    fadeOut(30, 255, 100);
//    fadeIn(100, 255, 100);
//  }

  fadeOut(255, 0);
  delay(7000);
  fadeIn(255, 255);
  fadeOut(0, 255);
  delay(7000);
}



