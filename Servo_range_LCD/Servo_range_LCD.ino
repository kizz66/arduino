#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo ServoGau;  // servo object #1

LiquidCrystal_I2C Screen(0x3f, 16, 2); // i2c address 0x27 3f

int pos = 1500;          // middle position variable  ( 1400-1600 depens on servo model)
int mem;

void setup()
{
  // pinMode(8, INPUT_PULLUP);
  // pinMode(9, INPUT_PULLUP);

  ServoGau.attach(10);                // attache servo signal on pin 10
  ServoGau.writeMicroseconds(pos);  // set initial position (center)

  Screen.init();
  Screen.backlight();
  Screen.clear();                    //clear the LCD during setup
  Screen.setCursor(0, 0);
  Screen.print("microsec:");
  delay(5000);
}


void loop()
{
  //-  connect potentiometer to analog input #A0

  pos = analogRead(1);
  if (abs(pos - mem) > 2) {
    mem = pos;
    pos = map(pos, 0, 1023, 540, 2400);
    ServoGau.writeMicroseconds(pos);
    Screen.setCursor(0, 1);
    Screen.print(pos);
  }
  delay(5);
}



