/*
Base code for ArdSim LAN/USB Library.
Upload and connect buttons / switches to any 
digital inputs accordingly with your input config file to test

Download ArdSim Library on the SimVim Design website:
http://svglobe.com
 */



//================================ 
#include <SPI.h> 
#include <Ethernet.h>         // -- comment or delete these two lines if USB is used   
//================================ 
//================================ 
#include <ArdSim_Interface.h>         //  -- ArdSim library 
//================================ 



#define  PitotHeat 13, 5       // Pitot heat indicator (output pin #13, dataref #5)
//------------------------------------------
void setup()  { 
  
    BoardNumber 1;            // -- Assign Board Number here  (0...9)


} 

//------------------------------------------
void loop()   { 
  
     ArdSimScan;               // main loop  - scan inputs and read incoming data for output

     LEDout(PitotHeat);        // pitot heat indicator
   
}      
//===========================================


