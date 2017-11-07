#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ArdSimX_Interface.h>

LiquidCrystal_I2C lcd(0x3f, 16, 2); // i2c address 0x27

int outValues[9]; // 0-6 autopilot status 7- Autopilot ALT 8 - VVI

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
   // ALT
  if (id == 8 ) {
    outValues[id - 1] = val;
    renderAlt();
  }
    // VVI
  if (id == 9 ) {
    outValues[id - 1] = val;
    renderVs();
  }
}

void renderAlt(void) {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print(outValues[7]);
}

void renderVs(void) {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print(outValues[8]);
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

7 - Gear is Down (Green light for each gear)
8 - Gear is Unsafe ( red lamps for each gear)
9 - Autopilot Vertical Speed set, encoder
13 - Autopilot Altitude pre-set, encoder

---- Analog pins: ----

0 - Mixture control, all
1 - Landing gear down (end-switch) / Landing gear up ( end-switch)
2 - Flaps Down ( - notch) position
3 - Flaps Up ( + notch) position

---- Matrix: ----

1 - Altitude-hold ARM (pre-selected ALT)

---- Programmable outputs: ----

1 - Flight director mode
2 - Heading mode status
3 - Backcourse mode status
4 - Approach mode status
5 - Nav mode status
6 - Altitude hold status
7 - Vvi mode status
8 - Altitude to hold dialed into the AP
9 - VVI commanded display



@ ================= CONFIG =================

*1-4Ui
[A]
B 2 4 5 6 11
[I]
e13- sim/autopilot/altitude_down
e13+ sim/autopilot/altitude_up
e9- sim/autopilot/vertical_speed_down
e9+ sim/autopilot/vertical_speed_up
A3+ sim/flight_controls/flaps_up
A2+ sim/flight_controls/flaps_down
A1- sim/flight_controls/landing_gear_down
A1+ sim/flight_controls/landing_gear_up
A0 sim/cockpit2/engine/actuators/mixture_ratio_all 0,1 1 100 0 100
B1+ sim/autopilot/altitude_arm
[O]
1D 0 sim/cockpit2/autopilot/flight_director_mode
2D 0 sim/cockpit2/autopilot/heading_status
3D 0 sim/cockpit2/autopilot/backcourse_status
4D 0 sim/cockpit2/autopilot/approach_status
5D 0 sim/cockpit2/autopilot/nav_status
6D 0 sim/cockpit2/autopilot/altitude_hold_status
7D 0 sim/cockpit2/autopilot/vvi_status
10S 2 sim/cockpit2/controls/flap_handle_deploy_ratio 1 0,1 1000,1800
8D -1 sim/cockpit2/autopilot/altitude_dial_ft 1
7L 1 sim/flightmodel2/gear/deploy_ratio 1
8L 0 sim/flightmodel2/gear/deploy_ratio 1 0.01 0.99
9D -1 sim/cockpit2/autopilot/vvi_dial_fpm 1
*/
