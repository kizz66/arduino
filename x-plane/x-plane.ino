#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ArdSimX_Interface.h>

LiquidCrystal_I2C lcd(0x3f, 16, 2); // i2c address 0x27

int outValues[8]; // 0-6 autopilot status 7- VS

void setup()  {
  BoardNumber 1;// -- Assign Board Number here  (0...9)
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("ready");
  delay(2000);
  lcd.clear();
}

void loop()   {
  ArdSimScan;
}

void ProgOut(byte id, float val) {

  // AP status
  if (id >= 1 && id <= 7 ) {
    outValues[id - 1] = val;
    renderApStatus();
  }
   // ALT / VS
  if (id == 8 ) {
    outValues[id - 1] = val;
    renderAltAndVs();
  }
}

void renderAltAndVs(void) {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print(outValues[7]);
}

void renderApStatus(void) {
  lcd.clear();
  lcd.setCursor(0, 0);  if (outValues[0] > 0)  lcd.print("FD");
  lcd.setCursor(14, 0); if (outValues[0] == 2) lcd.print("AP");

  lcd.setCursor(0, 1);  if (outValues[1] == 2) lcd.print("HDG");
  lcd.setCursor(0, 1);  if (outValues[2] > 0)  lcd.print("BC ");
   
  lcd.setCursor(4, 1);  if (outValues[3] > 0)  lcd.print("APPR");
  lcd.setCursor(4, 0);  if (outValues[4] > 0)  lcd.print("NAV");
  
  lcd.setCursor(9, 0);  if (outValues[5] == 2) lcd.print("ALT");
  lcd.setCursor(9, 0);  if (outValues[6] == 2) lcd.print("V/S");
}

/*  Lines in the "data.cfg"  file:
@ ================= INFO =================

Board #1 - Arduino (USB) + i2c -------------------------------------------------------

---- Digital pins: ----


---- Analog pins: ----

2 - Vertical speed, at pre-selected VSI.
3 - Altitude-hold ARM (pre-selected ALT)

---- Programmable inputs: ----


---- Programmable outputs: ----

1 - Flight director mode
2 - Heading mode status
3 - Backcourse mode status
4 - Approach mode status
5 - Nav mode status
6 - Altitude hold status
7 - Vvi mode status
8 - Combined Alt/VVI selector display shows VVI or ALT



@ ================= CONFIG =================

*1-4Ui
[A]
[I]
A2+ sim/autopilot/vertical_speed_pre_sel
A3+ sim/autopilot/altitude_arm
[O]
1D 0 sim/cockpit2/autopilot/flight_director_mode
2D 0 sim/cockpit2/autopilot/heading_status
3D 0 sim/cockpit2/autopilot/backcourse_status
4D 0 sim/cockpit2/autopilot/approach_status
5D 0 sim/cockpit2/autopilot/nav_status
6D 0 sim/cockpit2/autopilot/altitude_hold_status
7D 0 sim/cockpit2/autopilot/vvi_status
10S 2 sim/cockpit2/controls/flap_handle_deploy_ratio 1 0,1 1000,1800
8D 0 sim/cockpit2/autopilot/alt_vvi_is_showing_vvi 1
*/
