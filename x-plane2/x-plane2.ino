#include <SPI.h>
#include <ArdSim_Interface.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3f, 16, 2);

#define Flap    10, 0, 1, 560, 2100 // servo on pin #10

float data;

void setup()  {
  BoardNumber 1;
  lcd.init();
  lcd.backlight();
}

void loop()  {
  ArdSimScan;
  servoGauge (2, Flap);

  if ( NewData (6) ) {
    data = GetData ( 6 );
    lcd.setCursor(0, 1);
    lcd.print(data);
  }
  if ( NewData (2) ) {
    data = GetData ( 2 );
    lcd.setCursor(0, 1);
    lcd.print(data);
  }
}

void ProgOut(byte id, float val) {
  switch (id) {
    case 1: lcd.setCursor(0, 0);  if (val > 0)  lcd.print("FD");   else lcd.print("  ");
      lcd.setCursor(14, 0); if (val == 2) lcd.print("AP");   else lcd.print("  ");   break;
    case 2: lcd.setCursor(0, 1);  if (val == 2) lcd.print("HDG");  else lcd.print("   ");  break;
    case 3: lcd.setCursor(0, 1);  if (val > 0)  lcd.print("BC");   else lcd.print("  ");   break;
    case 4: lcd.setCursor(4, 1);  if (val > 0)  lcd.print("APPR"); else lcd.print("    "); break;
    case 5: lcd.setCursor(4, 0);  if (val > 0)  lcd.print("NAV");  else lcd.print("   ");  break;
    case 6: lcd.setCursor(9, 0);  if (val == 2) lcd.print("ALT");  else lcd.print("   ");  break;
    case 7: lcd.setCursor(9, 0);  if (val == 2) lcd.print("V/S");  else lcd.print("   ");  break;
    case 8: lcd.setCursor(10, 1); if (val == 1) lcd.print("YAW");  else lcd.print("   ");  break;
  }
}
