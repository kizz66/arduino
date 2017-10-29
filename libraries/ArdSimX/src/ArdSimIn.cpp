#include "ArdSimIn.h"
void ArdSimIn::dIn(byte isr, byte p) { byte in = digitalRead(p); // dbnc=0;
if (in != bitRead(flags[p], 4) || isr==1) { bitWrite(flags[p], 4, in); 		
com.prtCom (1, p, in+1);   dbnc=millis();  } }
void ArdSimIn::eIn(byte mod, byte i) { 
byte in;  byte enc=0; int edir=0; 
in=conf[6]; if (mod==2) in=i; if (mod==3) digitalWrite(i, LOW); // d // m
byte em = (flags[i]&96)>>5;	enc=!digitalRead(in+1); enc=enc<<1; enc=enc|!digitalRead(in);
if (enc != em) { int dir=1; 
for (int m=0; m<80; m++) {  if(m!=0) { 	enc=!digitalRead(in+1); enc=enc<<1; enc=enc|!digitalRead(in);}
switch (em) { case 0: if (enc == 1 )  edir++;  else if (enc == 2 ) edir--; break;
case 1: if (enc == 3 )  edir++;  else if (enc == 0 ) edir--; break; 
case 2: if (enc == 0 )  edir++;  else if (enc == 3 ) edir--; break;
case 3: if (enc == 2 )  edir++;  else if (enc == 1 ) edir--; break;	}   em = enc;	delayMicroseconds(800);		}		
if (edir<0) dir=2; edir=abs(edir); if (edir<edel) edir=1; if (edir>espd) edir=edir*2; 
while (edir!=0) { com.prtCom (0, i, dir); edir--; } enc<<=5;							
flags[i] = enc+(flags[i]&159);  if (mod==3) digitalWrite(i, HIGH);  return; } //  active enc
if (mod==3)	digitalWrite(i, HIGH); 	 }	 //   close row
void ArdSimIn::mxIn(byte isr) { mdbn=0; byte Act=-1; int a;  int c; byte in;
for (int i = conf[10]; i <= conf[11]; i++)  {digitalWrite(i, LOW); 
for (int j = conf[8]; j <= conf[9]; j++)  { Act++; in = digitalRead(j); 
a=Act/16;  c=Act-(16*a);
if (in != bitRead(mxflag[a], c) || isr==1) { Act++; bitWrite(mxflag[a], c, in);	
com.prtCom (3, Act, in+1); mdbn=millis();  if (isr==0) {  digitalWrite(i, HIGH); return; } } 
} digitalWrite(i, HIGH); } }
void ArdSimIn::aIn(byte isr) { int Ain; int min;	int max; int pre; byte t=5;
for (int i=0; i<a_pins; i++) { pre=aflags[i];
if (pre>0) { if (pre==1) AnDig(i, isr);	else { t=2;
min=(102*a_min[i])/10;  max=(102*a_max[i])/10; 
if (aflags[i]>128) { t=5; pre=aflags[i]-128; }
if (pre>50) { pre=pre*100; pre-=10000; } int sence = 1024/pre;  
Ain=constrain(analogRead(i), min, max ); if (t==2) Ain = map(Ain, min, max, 0, 1023); 
int pos = round(float(Ain)/sence); if (A_pos[i] != pos || isr==1) { A_pos[i] = pos; 
if (t==2)  pos = constrain(map(pos, 0, pre, 0, 1000), 0, 1000); else pos++;  itoa(pos, com.dfv, 10); 
com.prtCom(t, i, pos);  if (isr==0 && t==5 ) return; } }}}}// for mp
void ArdSimIn::AnDig(int pin, byte isr) { //---- an digital
int a=pin; switch (a) { 							
case 0: a=A0; break; case 1: a=A1; break; case 2: a=A2; break; case 3: a=A3; break; 
case 4: a=A4; break; case 5: a=A5; break; case 6: a=A6; break; case 7: a=A7; break; 
#if (defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__))
case 8: a=A8; break; case 9: a=A9; break; case 10: a=A10; break; case 11: a=A11; break; 
case 12: a=A12; break; case 13: a=A13; break; case 14: a=A14; break; case 15: a=A15; break;
#endif
} int pos = digitalRead(a);
if (A_pos[pin] != pos || isr==1) { A_pos[pin] = pos;  com.prtCom(6, pin, pos+1); }}//analog d
ArdSimIn::ArdSimIn() { }
ArdSimIn inp = ArdSimIn();
