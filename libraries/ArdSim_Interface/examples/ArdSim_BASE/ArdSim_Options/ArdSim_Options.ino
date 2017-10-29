/*
Base code for ArdSim LAN/USB Library.
Options: 
- set IP addresses for X-Plane PC and Arduino
- set MAC address if it present on the shield stiker
- change USB serial speed rate)

Download ARDsim Library on the SimVim Design website:
http://svglobe.com
 */



//================================ 
#include <SPI.h> 
#include <Ethernet.h>         // -- comment or delete these two lines if USB is used   
//================================ 
//================================ 
#include <ArdSim_Interface.h>          //  -- ArdSim library 
//================================ 


void setup()  { 
  
	BoardNumber 1;   // - board number from 1  to 9


//serial = 115200;      // change USB serial speed (change in the config.ini file too)

//XPLANE_IP (192,168,0,104);  // set IP address of X-Plane PC
//ARDUINO_IP (192,168,0,3);   //  set IP address of Arduino
//ardsimPort = 5080;				// change port number if nedeed (in the config.ini file too)
//MAC_ADDR ( 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xFF );  // If you have label with MAX address on your Ethernet shield 

} 

//------------------------------------------
void loop()   { 
  
     ArdSimScan; 
   
    

}      
//========================================


