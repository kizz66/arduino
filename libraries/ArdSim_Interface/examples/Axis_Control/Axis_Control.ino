/*
ArdSim Analog input demonstration 
by Vlad Sychev 2012-2016
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


#define Throttle1 1        // you can define your constant ...

//---------------------------------------------
void setup()  { 
 
      BoardNumber 1;  //Assign Board Number!  (0...9)
  
    
  AnalogIn(0, 100);  // simple analog input, precision = 100 steps, full-range pot)
  AnalogIn(Throttle1, 200, 10, 800); // precision = 200, pot has value range  10-800  

   
    /*  !!  Comment or delete lines with unused Analog inputs to prevent 
            scanning open inputs and unintentional sending the input interference data   */

  }
  
//--------------------------
void loop()  { 

    ArdSimScan; // scan and send all inputs and read data for output




 } 
 //===== end =============


/* 
input config file sample in_1.cfg:

===================================

A0  sim/cockpit2/engine/actuators/cowl_flap_ratio   0,1   1 
A1  sim/cockpit2/engine/actuators/throttle_ratio   0,1   1

*/




