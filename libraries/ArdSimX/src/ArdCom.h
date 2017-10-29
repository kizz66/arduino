/*	ArdSimX Interface */
#ifndef ArdCom_h
#define ArdCom_h
#include "Arduino.h"
#include "ArdSimIn.h"
#define SW Serial.write
#define DOUT digitalWrite
#define RES 100
#define SlaveInit  Wire.onReceive(ReadMaster)
#define REGS { DOUT(p, r&1); DOUT(n, 1); r>>=1; DOUT(n, 0); }
#define REGW DOUT(l, 1); DOUT(l, 0); 
#define STEP  DOUT(s,HIGH); DOUT(s,LOW);
#define DMS  delayMicroseconds
void SlaveWrite(int num, float val);
class ArdCom {
public:
ArdCom();
void SimGet(int mode);
void SimReset(byte r);
void prtCom(byte type, byte in=0, int val=0);
void S_set();
byte xData(byte n=0, int d=0);
char dfv[8];
char rm[5];
union { byte bv[4]; float fv; } fval;
char to_slave[5];
byte ARD=1;
int ps=0;
byte db[64];
byte inx;
char act='-';
void StPos(byte s);
void StRes();
#if (defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__))
word stm[54];	 
int rst[4][54];  
#else
word stm[14];	
int rst[4][14];  
#endif
int sGau[10];
byte srvpin[10];
byte snum=255; //s count
unsigned long stime;    // s timer
unsigned long rtime; 
private:
};
extern ArdCom com;
extern byte XData(byte n=0, int d=0);
extern void SlaveOUT();
extern void ProgOut(byte data, float val);
extern void Scan(byte isr);
extern void ModeSet(byte pin, byte in);
extern unsigned long cy; 
extern byte ucom;
extern byte conf[];
extern byte flags[];
extern byte d_pins;
extern byte start;
#endif
