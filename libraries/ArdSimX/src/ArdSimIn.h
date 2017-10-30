#ifndef ArdSimIn_h
#define ArdSimIn_h
#include "ArdCom.h"
class ArdSimIn
{
public:
ArdSimIn();
void aIn(byte isr); 
void AnDig(int a, byte is);
void dIn(byte isr, byte pin);
void eIn(byte mod, byte pin); 
void mxIn(byte isr); 
unsigned long atime; 
unsigned long mdbn;
unsigned long dbnc; 
int edel=15;
int espd=18;
#if (defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__))
int A_pos[16];    		
byte a_min[16];	byte a_max[16];	
byte aflags[16];	  
byte a_pins=16;
word mxflag[16];  
#elif (defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega328__))
int A_pos[8]; 
byte a_min[8]; byte a_max[8];	
byte aflags[8];
byte a_pins=8;
word mxflag[5];
#elif (defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__))
int A_pos[6];   
byte a_min[6]; byte a_max[6];	
byte aflags[6];	
byte a_pins=6;
word mxflag[5];
#endif
private:
};
extern ArdSimIn inp; 
#endif
