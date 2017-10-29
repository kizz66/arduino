#include <Ethernet.h>
#include <ArdSimX_Interface.h>

void setup()  { 
BoardNumber 1;   // - board number from 1  to 9
MAC_ADDR ( 0x0E, 0x94, 0x05, 0xCB, 0x19, 0x50 );  
XPLANE_IP (192,168,1,6);
ARDUINO_IP (192,168,1,3);
ARDSIM_PORT 5080;
} 

void loop()   { 
     ArdSimScan; 
}      

void ProgOut(byte id, float val) {
	if (id==1) {  }
	else if (id==2 && val>0) {    }
//.. etc., or use "case"
}

