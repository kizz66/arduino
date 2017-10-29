/*
	ArdSim input/output interface for cockpit simulator. 
	The latest version of this library, manuals and code samples at SimVimDesign:
	http://svglobe.com
	Ver 5.4 (Mar. 2016)
*/
#ifndef ArdSim_h
#define ArdSim_h
#include "SimIn.h" 
#if (defined (ethernet_h) || defined (UIPETHERNET_H))
EthernetUDP Udp; 
IPAddress ipa (0,0,0,0); 
IPAddress ipx (0,0,0,0);
int ardsimPort=5080;
byte mac_ad[6]={ 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte xData(byte n, byte d) { 
 switch(n) { case 0:  sim.lan=1; break; 
case 1: sim.ps=Udp.parsePacket();  return sim.ps; break; 
case 2: Udp.write(d); break; case 3: Udp.write(sim.value); break; 
case 4: if (d==62) Udp.beginPacket(ipx, ardsimPort); else Udp.endPacket(); break; 
case 5: Udp.beginPacket(ipx, sim.xport); break;  
case 6: sim.inx=Udp.read(); return sim.inx; break; case 7: Udp.read(sim.db, d); break;  
case 8: Udp.write(sim.DREF); break;  
case 9: ipx=Udp.remoteIP(); break;
case 10: Ethernet.begin(mac_ad); ipa=Ethernet.localIP(); break; 
case 11: Ethernet.begin(mac_ad, ipa); Udp.begin(ardsimPort); break; 
case 12: mac_ad[5]=0xEC+sim.ARD ; break;  } return 0; }
void ARDUINO_IP(byte a1,byte a2,byte a3,byte a4) { ipa[0]=a1; ipa[1]=a2; ipa[2]=a3; ipa[3]=a4;  sim.is_ipa=1;	}
void XPLANE_IP(byte a1,byte a2,byte a3,byte a4) { ipx[0]=a1; ipx[1]=a2; ipx[2]=a3; ipx[3]=a4;  sim.is_ipx=1; }
void MAC_ADDR(byte a1,byte a2,byte a3,byte a4,byte a5,byte a6) {
mac_ad[0]=a1; mac_ad[1]=a2; mac_ad[2]=a3; mac_ad[3]=a4; 
mac_ad[4]=a5; mac_ad[5]=a6;  sim.is_mac=1; }
#else
long serial=115200;
byte xData(byte n, byte d) { 
 switch(n) { case 0: Serial.begin(serial); sim.lan=0; break; 
case 1: sim.ps=Serial.available(); return sim.ps; break; 
case 2: Serial.write(d);  break; 
case 3: Serial.write(sim.value); break; 
case 4: Serial.write(d); break; 
case 6: sim.inx=Serial.read(); return sim.inx; break; } return 0; }
#endif
#ifdef TwoWire_h
#define SlaveInit  Wire.onReceive(ReadMaster)
int slave=2;
void SlaveOUT(byte s) { Wire.beginTransmission(s); \
for (int n=0; n<6; n++) Wire.write(sim.to_slave[n]); Wire.endTransmission();} 
void ReadMaster(int c=0) { for (int n=0;n<6;n++) sim.to_slave[n]= Wire.read(); GetMaster();}
#endif
byte conf[10]; 
//-----------------------------------
#if (defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__))
byte flags[54]; 
byte d_pins=54;  
#else
byte flags[14]; //*
byte d_pins=14; 
#endif
//-----------------------------------------
#endif




