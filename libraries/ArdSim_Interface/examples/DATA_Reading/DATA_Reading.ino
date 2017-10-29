/*  Read dataref values in ArdSim Library
for using in your custom code

by Vlad Sychev 2012-2016
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


int Nav1st;   // Nav1 stanby freq.


//---------------------
void setup()  { 
 
BoardNumber 1;
 
   
  }
  
//--------------------------
void loop()  { 

ArdSimScan; 

 // to get the current dataref value use the GetData function with dataref number
 
 Nav1st = GetData(30);    // read dataref #30 every time, no matter if it changes or not.
 
 
// -- use the NewData function to check if the DataRef has changed.
// This will save program time by ignoring values that remained the same.
 

if (NewData(30)) { 
  
  Nav1st = GetData (30);
  
      // your code 
      }


} 
 //=======================

/*   place  this line in your output config file:

30 0 sim/cockpit2/radios/actuators/nav1_standby_frequency_hz

*/

