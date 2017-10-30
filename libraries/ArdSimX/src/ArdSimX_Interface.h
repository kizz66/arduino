/* ArdSimX - the input/output interface for X-Plane simulator. 
	The latest version, manuals and code samples at http://www.simvim.com
	Copyright © SimVim 20012-2017
	Ver 1.9  (8 June 2017)  */
#ifndef ArdUcom_h
#define ArdUcom_h
//#include <SPI.h> 
#include "ArdCom.h"
#define ArdSimScan SimScan()
#define BoardNumber com.ARD=
#define USB_Serial serial=
#define ARDSIM_PORT ardsimPort=
#define prec *10000
#if (defined (ethernet_h) || defined (UIPETHERNET_H))
EthernetUDP Udp; 
IPAddress ipa (0,0,0,0); 
IPAddress ipx (0,0,0,0);
int ardsimPort=5080;
byte mac_ad[6]={ 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEC };
byte is_mac=0;
byte is_ipa;
byte is_ipx;
byte XData(byte n, int d) {
switch(n) { case 0: if (is_mac==0) mac_ad[5]=0xEC+com.ARD ; 
if (is_ipa==0) { Ethernet.begin(mac_ad); ipa=Ethernet.localIP(); } 
Ethernet.begin(mac_ad, ipa); Udp.begin(ardsimPort);
if (is_ipx==0) { while (com.ps==0) XData(1); XData(9); } break; 
case 1: com.ps=Udp.parsePacket();  return com.ps; break; 
case 2: Udp.write(d); break; case 3: Udp.write(com.dfv); com.dfv[4]=0; break; 
case 4: Udp.beginPacket(ipx, ardsimPort); break; case 5: Udp.endPacket(); break;  
case 6: com.inx=Udp.read(); return com.inx; break; case 7: Udp.read(com.db, d); break;  
case 9: ipx=Udp.remoteIP(); break;   } return 0; }
void ARDUINO_IP(byte a1,byte a2,byte a3,byte a4) { ipa[0]=a1; ipa[1]=a2; ipa[2]=a3; ipa[3]=a4;  is_ipa=1;	}
void XPLANE_IP(byte a1,byte a2,byte a3,byte a4) { ipx[0]=a1; ipx[1]=a2; ipx[2]=a3; ipx[3]=a4;  is_ipx=1; }
void MAC_ADDR(byte a1,byte a2,byte a3,byte a4,byte a5,byte a6) {
mac_ad[0]=a1; mac_ad[1]=a2; mac_ad[2]=a3; mac_ad[3]=a4; 
mac_ad[4]=a5; mac_ad[5]=a6;  is_mac=1; }
#else
long serial=115200;
byte XData(byte n, int d) { Serial.begin(serial); ucom=1; return n+d; }
#endif
#ifdef TwoWire_h
#define SlaveInit  Wire.onReceive(ReadMaster)
boolean itoc=1;
int slave=2;
void SlaveOUT() { Wire.beginTransmission(slave); 
for (int n=0; n<5; n++) Wire.write(com.to_slave[n]);  Wire.endTransmission();} 
void ReadMaster(int c) { union { byte byte_v[4]; float fl_v; } ftob; 
int idx=Wire.read(); for (int n=0;n<4;n++) ftob.byte_v[n]= Wire.read();
if (c) c=1;   idx+=ftob.byte_v[0];}
#else
boolean itoc=0;
void ReadMaster(int c) { if (c) c=1; } //dum
void SlaveOUT() { ReadMaster(0); }; //d
#endif
byte conf[14];  
unsigned long cy; 
unsigned long scan;
byte start=0;
byte ucom=0;
#if (defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__))
byte flags[54]; 
byte d_pins=54;  
#else
byte flags[14]; //*
byte d_pins=14; 
#endif
void SimInput(byte num, float val) { com.rm[0]=0;
long fmain = long(val); val = abs(val-fmain)+1;
int frem=int(val prec); ltoa(fmain, com.dfv, 10); 
if (val>1) { itoa(frem, com.rm, 10); com.rm[0]='.'; }
com.prtCom(4,num); }
void SimScan() { 
if (start) { cy=micros()-scan; scan=micros();  com.SimGet(0);  Scan(0); } 
else { delay (500); XData(); delay (500);  com.SimReset(0); }  }
void Scan(byte isr) { byte mod; 
for (int i = 0; i < d_pins; i++) { mod=flags[i]&15;  
if ((mod==1 && millis()-inp.dbnc>30) || (mod==1 && isr==1)) inp.dIn(isr, i); 
else if ((mod==2 || mod==3) && isr==0) inp.eIn(mod, i); 
else if ((mod==9 || mod==10) && com.rst[1][i]!=0) com.StPos(i);	}
if (conf[8]<100 && millis()-inp.mdbn>25) inp.mxIn(isr); 
if (millis() - inp.atime > 25) { inp.aIn(isr);	inp.atime = millis();  }
if (com.snum!=255 && (millis()-com.rtime)<2000) com.S_set();}
void ModeSet(byte pin, byte in) { if (in<16) { flags[pin]=(flags[pin]&240)+in; 
if (in>5 || in==3) pinMode(pin, OUTPUT);
else { if ( pin==13) pinMode(pin, INPUT); else	pinMode(pin, INPUT_PULLUP); }
switch (in) { case 2:  pinMode(pin+1, INPUT_PULLUP); break; 
case 3:  DOUT(pin, HIGH); break; 
case 4:  conf[6] = pin; pinMode(pin+1, INPUT_PULLUP); break; 
case 6:  DOUT(pin, HIGH); break; case 9:  DOUT(pin,LOW); break; 
case 10: DOUT(pin,LOW); pinMode(pin+1, INPUT_PULLUP); break; 
case 11: DOUT(pin,LOW); conf[7]=pin; break; 
case 12: com.snum++; com.srvpin[com.snum]=pin; break; 
case 13: conf[12]=pin; conf[13]=pin+1; pinMode(pin+1, OUTPUT); break; } }       
else  { 
#if (defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__))
pin+=54; 
#elif (defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega328__))
pin+=18; 
#else
pin+=14; 
#endif // adiinout
if (in=='D') pinMode(pin, INPUT_PULLUP); 
else if (in=='O') pinMode(pin, OUTPUT); } 	 }
//-----------------------------------------
#endif
