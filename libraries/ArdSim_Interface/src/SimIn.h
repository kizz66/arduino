/*
	ArdSim input/output interface for cockpit simulator. 
	The latest version of this library, manuals and code samples at SimVimDesign:
	http://svglobe.com
	Ver 5.4 (Mar. 2016)
*/
#ifndef SimIn_h
#define SimIn_h
#include "Arduino.h"
#include "SimIn.h"
#define DIRECT 1
#define STATIC 2
#define ON 255
#define OFF 0
#define MX 222
#define NOINPUT 100
#define ALL 222
#define BoardNumber sim.ARD=
#define ArdSimScan sim.SimScan()
#define SGau() servoGauge(byte srv, byte num, byte pin, float min, float max, int smin, int smax)
void InputMatrix(byte X1, byte X2, byte Y1, byte Y2);
void EncoderPort(byte port);
void EncoderPin(byte pin,  byte btn=0);
void EncModeBtn(byte pin, byte enc, byte id, byte mx=0);
byte EncMode(byte enc);
void EncModeLED(byte pin, byte enc, byte mod);
void RepeatBtn(byte num, byte mx=0);  
void AnalogIn(byte pin, word pre, word min=0, word max=1023); 
void AnalogSwitch(byte pin, word pos);
boolean ReadInput (byte pin, byte act=2, byte mx=0);
byte CountButton (byte pin, byte mode, byte cm);
void SimInput(byte id);
float GetData(byte idx);
boolean NewData(byte idx);
void LEDout(byte pin, byte dref, float val=1, float val1=-999, boolean inv=0);
void Gauge ( byte num, byte pin, float min, float max, int smin=0, int smax=100);
void servoGauge (byte num, byte pin, float min, float max, int smin, int smax);
void OutputPin(byte pin, byte last=0);
void InputPin(byte pin=222, byte last=0);
void SendToSlave(byte s, byte d0, byte d1=0, byte d2=0, byte d3=0, byte d4=0);
void GetMaster();
void SetData(byte idx, float val);
//----test -------------
void StepPos (byte st, int pos);
void StepGauge (byte A, byte B, byte mid, byte dref, float min, float max );
void StepperGauges();
void ARDUINO_IP(byte a1,byte a2,byte a3,byte a4);
void XPLANE_IP(byte a1,byte a2,byte a3,byte a4);
void MAC_ADDR(byte a1,byte a2,byte a3,byte a4,byte a5,byte a6);
//---------------- 	//XPD
void XPDref (char* DRef, float Val);
void XPCmnd (char* Com);
void XPMenu (int MenuNum); 
class ARDsim
{
public:
ARDsim();
void SimScan();
void SimStart();  //  setup
void Comm();
void SClr();
void ArdInit();
boolean ToSlave(byte data);
void SendPack(char* str, byte num);
void Scan();
void EncIn();
void MxIn();
void DirIn();
void AnIn();
void PinSet(byte pin, byte in=0); // 0 - in, 1 - out 
void AIn(byte num,  int val, byte type);
void Send(byte type, int num, byte dir=0, byte mode=0);
char inits; 	
word tscan;		

char* DREF;

byte to_slave[6];
byte start=0;
long serial=115200;
int ps;
byte inx;
char value[5];
int lan=1;
unsigned int xport=49000;
byte is_mac=0;
boolean is_ipx=0;
boolean is_ipa=0;
char ardn[5] = {'|','A','R','1','-'};
byte ARD;
byte w_pin;        // wire
byte in_pin=0; 
unsigned long atime;     // timer ( 25 ms )
unsigned long inscan; 
unsigned long dbnc; 
#if not (defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__))
int sGau[10];
byte srvpin[10];
byte db[64];
float Dget[10]; 
word mxflag[5];
word mxhold[5];
byte brd=0;
#endif
#if (defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__))
int sGau[20];
byte srvpin[20];
byte db[256];
float Dget[50]; 
int A_pos[16];    		 // prev pos (0-1000)
byte a_min[16];	byte a_max[16];		 // 0-100%
word aflags[16];	     // 2-50 pos + 100,200...1000 (2-110) +bit 127 if switch
word a_set[16];
byte a_pins=16;
word mxflag[16];
word mxhold[16];
byte brd=1;
#elif (defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega328__))
int A_pos[8]; 
byte a_min[8]; byte a_max[8];	 // 0-100%
word aflags[8];
word a_set[8];
byte a_pins=8;
#elif (defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__))
int A_pos[6];   
byte a_min[6]; byte a_max[6];	 // 0-100%
word aflags[6];	
word a_set[6];
byte a_pins=6;
#endif

byte mxa; 
byte cbtn;
boolean cb=0; 
byte Act; 
boolean active;
boolean tabu;
byte iscan=2;
byte Emem[25];			//  enc+btn last state 
byte Etyp[25];			//  enc+btn type
byte Emode[25];				//  mode 0, 1.... 8, A, B, C...
byte Epins[28];   		// (0-24 -enc pins) +flags: 25-enab/type; 26-port, 27- enc number
int edel;
int espd;
byte Bx1;
byte Bx2;
byte By1;
byte By2;
//------------------------
void Timing();
byte snum; //srv count
byte srp; // prev srv pin
unsigned long stime;    // servo timer
//-----------
void stp_dn(byte st, int val);
void stp_up(byte st, int val);
void StepGau (byte st, int phase, int dir);
void StepRes();
byte A_coil[10];
byte mid[10];
byte B_coil[10]; 
byte sdref[10];
float stmin[10];
float stmax[10];
int mstep[10]; 
int abspos[10];
byte stn;
private:
};
extern ARDsim sim; 
extern byte xData(byte n=0, byte d=0);
extern void SlaveOUT(byte s);
extern byte flags[];
extern byte d_pins;
extern byte conf[];
#endif
