/*
ArdSim Library Output demonstration
Simple indicator controlled by dataref
Download ArdSim Library on the SimVim Design website:
http://svglobe.com
 */



//================================ 
#include <SPI.h> 
#include <Ethernet.h>         // -- comment or delete these two lines if USB is used   
//================================ 
//================================ 
#include <ArdSim_Interface.h>          //  -- ArdSim library 
//================================ 

#define  PitotHeat 13, 5              // Pitot heat indicator (output pin #13, dataref #5)

//-----------------------------------------------
void setup()  { 
 
  BoardNumber 1;  

}
//--------------------------

void loop()  { 

ArdSimScan;  

   LEDout(PitotHeat);              // pitot heat indicator
   
/* or you can use this function directly, without name definition:
   LEDout(13, 5);  */

/* To invert this LED  you can use value 0 in  "#define  PitotHeat 13, 5, 0 " or directly:    
   LEDout(13, 5, 0);     */

} 
//--- End -------------------

/* output config file out_1.cfg

For this example you should have this  dataref in the 5th line number:

===================================
1 ... 
2 ...
3 ...
4 ...
5  0  sim/cockpit2/annunciators/pitot_heat
6 ...
===================================

You should see:
LED on pin #13 will light up when the pitot heat dataref value is 1 (on)


*/




