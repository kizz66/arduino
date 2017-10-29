/*
	ArdSim input/output interface for cockpit simulator. 
	The latest version of this library, manuals and code samples at SimVimDesign:
	http://svglobe.com
	Ver 5.4 (Mar. 2016)
*/
#include "SimIn.h"
ARDsim::ARDsim() { }
ARDsim sim = ARDsim();
void  ARDsim::SimStart ()  {
inits='-';  delay(1000); 
xData();  ardn[3]=ARD+48; ardn[4]=inits; 
if (in_pin==0) {  if (lan==1) { for (int i=0; i<d_pins; i++) { 
if ((d_pins==54 && i<50 && i!=10) || (d_pins==14 && i<10)) PinSet(i, 0); } }
else { for (int i=2; i<d_pins; i++) PinSet(i, 0);  }}
if (lan==1) { if (is_mac==0) xData(12); if (is_ipa==0) xData(10);  xData(11); 
if (is_ipx==0) { while (ps==0) xData(1); xData(9); } while (conf[0]==0) Comm();  ArdInit();    }	
else {  while (conf[0]==0) { 
xData(4, '>'); SendPack(ardn, 5); xData(4, '<'); delay(500); Comm(); delay(500); } }
edel=5; espd=8; } // encoder correction  (test)
void ARDsim::SimScan() { 
if (iscan==2) { snum=255; 	iscan=1; return; }
if (start==0) { start=1;  SimStart (); }
if (stn!=0 && iscan==1) StepRes(); if (snum!=255) Timing(); if (stn!=0) StepperGauges();  
iscan=0; if (tscan>5000 && lan==0) { tscan=0; ardn[3]=ARD+48; ardn[4]=inits; 
xData(4, '>'); SendPack(ardn, 5); xData(4, '<');  } }
void ARDsim::PinSet(byte pin, byte in) {
if (in==1) { pinMode(pin, OUTPUT);  bitSet(flags[pin], 1); 
bitClear(flags[pin], 0); }
else { if ((flags[pin]&7)!=0) return;
if (pin==13) pinMode(pin, INPUT); else  pinMode(pin, INPUT_PULLUP);   
bitSet(flags[pin], 0); 	} if (in==2)  bitSet(flags[pin], 2);  }
void OutputPin(byte pin, byte last) {
if (last==0) sim.PinSet(pin, 1);
else for (int i=pin; i<=last; i++)  sim.PinSet(i, 1);	}
void InputPin(byte pin, byte last) {
if (pin==222) return;
	 sim.in_pin=1;
	if (pin==100) return;
	if (last==0) sim.PinSet(pin, 0);
	else for (int i=pin; i<=last; i++)  sim.PinSet(i, 0);
	}
byte EncMode(byte enc) { return sim.Emode[enc-1]; }  //if ((sim.Etyp[enc-1]&128)==0) return 0; else return sim.Emode[enc-1];
void EncModeLED(byte pin, byte enc, byte mod) {  
		if ((flags[pin]&2)==0)  sim.PinSet(pin, 1);
	if ((sim.Etyp[enc-1]&128)!=0) { if (sim.Emode[enc-1]==mod) digitalWrite(pin, 1); else digitalWrite(pin, 0);}
}
//------------------  Initial setup----------------------
void InputMatrix(byte X1, byte X2, byte Y1, byte Y2) {
    for (int x=X1; x<=X2; x++) { pinMode(x, INPUT_PULLUP);  bitSet(flags[x], 1); }
    for (int y=Y1; y<=Y2; y++) { pinMode(y, OUTPUT); digitalWrite(y, HIGH);  bitSet(flags[y], 1);}
		sim.Bx1 = X1; sim.Bx2 = X2; 
		sim.By1 = Y1; sim.By2 = Y2;  	 
  }
void EncoderPort(byte port) { 
	sim.Epins[25]=1;  sim.Epins[26] = port; 
	for (int x=port; x<=(port+2); x++) { pinMode(x, INPUT_PULLUP);  bitSet(flags[x], 1); }
	} 

void EncoderPin(byte pin,  byte btn) {
byte n=sim.Epins[27]; sim.Epins[27]++; 
sim.Epins[n]=pin; sim.Etyp[n] = btn; bitSet(sim.Etyp[n], 7); if (btn) sim.Emode[n]=1;
if (sim.Epins[25]!=1) { sim.Epins[25]=2; bitSet(flags[pin], 1);
bitSet(flags[pin+1], 1);  pinMode(pin, INPUT_PULLUP); pinMode(pin+1, INPUT_PULLUP); 
if (btn>0) { bitSet(flags[pin+2], 1); bitSet(sim.Emem[n], 4);  pinMode(pin+2, INPUT_PULLUP); }} 
else { pinMode(pin, OUTPUT); 	bitSet(flags[pin], 1); }}
void AnalogIn(byte pin, word pre, word min, word max) {
sim.a_set[pin]=max | (min<<10);  sim.aflags[pin]=pre-1; } 
void AnalogSwitch(byte pin, word pos) {
sim.a_set[pin] = 1023;   sim.aflags[pin]=pos-1;bitSet(sim.aflags[pin], 10);  }
void ARDsim::Scan() { cb=0;
if (Epins[25]>0 && iscan==0) EncIn(); if (By1!=By2 && Bx1!=Bx2) MxIn();
if (millis()-dbnc>20) DirIn(); AnIn(); }    
void ARDsim::EncIn() { 
int last=Epins[27]; byte enc=0; int edir=0; int in=26; 	 
for (int i = 0; i < last; i++)  { if (Epins[25]==2) in=i;	   
if (Epins[25]==1) digitalWrite(Epins[i], LOW); 
byte eb = Etyp[i]&15; 	byte em = Emem[i]&3;
//----------------------------intr ------------
if (eb > 0) { int btn = !digitalRead(Epins[in]+2);   
if (eb==1) Emode[i] = btn+1; else if (btn != bitRead(Emem[i], 2)) {
bitWrite(Emem[i], 2, btn);  bitClear(sim.Etyp[i], 7);
if (btn==0) { if (Emode[i] > 9) Emode[i] = 0;	 	
Emode[i]++; if (Emode[i]==eb+1) Emode[i]=1; bitSet(Etyp[i], 7);  }  		
if (Epins[25]==1) digitalWrite(Epins[i], HIGH);  
delay(15);   return;  } } 								
//-----------------------------------------------------------------------------	
enc=!digitalRead(Epins[in]+1); enc=enc<<1; enc=enc|!digitalRead(Epins[in]);
if (enc != em) { int e=1; 
for (int m=0; m<80; m++) {  if(m!=0) { enc=!digitalRead(Epins[in]+1); enc=enc<<1; enc=enc|!digitalRead(Epins[in]);}
switch (em) { 
case 0: if (enc == 1 )  edir++;  else if (enc == 2 ) edir--; break;
case 1: if (enc == 3 )  edir++;  else if (enc == 0 ) edir--; break; 
case 2: if (enc == 0 )  edir++;  else if (enc == 3 ) edir--; break;
case 3: if (enc == 2 )  edir++;  else if (enc == 1 ) edir--; break;	
}  em = enc;	delayMicroseconds(800);		}		
if (edir<0) e=2; edir=abs(edir); if (edir<edel) edir=1; if (edir>espd) edir=edir*2; 
while (edir!=0) { Send (0, i+1, e, Emode[i]); edir--; }									
Emem[i] = enc+(Emem[i]&4);	if (Epins[25]==1) 	digitalWrite(Epins[i], HIGH);  return;
} if (Epins[25]==1)	digitalWrite(Epins[i], HIGH); } } 
void ARDsim::MxIn() { 
		 int a;  int c;
		for (int i = By1; i <= By2; i++)  {
			digitalWrite(i, LOW); 
			for (int j = Bx1; j <= Bx2; j++)  { Act++;
			 active = digitalRead(j); 
				a=Act/16;  c=Act-(16*a);
		   	if (active != bitRead(mxflag[a], c) || iscan==1) { Act++;
				bitWrite(mxflag[a], c, active);	
				Send (3, Act, active+1); 
 			delay(15);	 mxa=222; if (iscan==0) { digitalWrite(i, HIGH);   return; }  }
				} digitalWrite(i, HIGH); 
				}  mxa=0;	}
void ARDsim::DirIn() {   dbnc=0; //int p=0; if (lan==0) p=2;			
		for (byte i = 0; i < d_pins; i++)  { 
			 if ((flags[i]&1) !=0) { active = digitalRead(i); 
				if (active != bitRead(flags[i], 3)  || iscan==1) 
					{ bitWrite(flags[i], 3, active);  Act = i; 
					Send (1, i, active+1); dbnc=millis(); 
		if((flags[i]&4) !=0 && active==0) {  byte cn=(flags[i]&112)>>4;  
					cn=(cn+1)<<4;  flags[i]=cn+(flags[i]&143);  }
				if (iscan==0) return ;	}
				} 	}  }
void ARDsim::AnIn() { 
	if ((millis() - atime > 25) || iscan==1)
	 { int Ain; int min;	int max; int pre; byte t;
		for (int i=0; i<a_pins; i++) if (aflags[i]>0) { 
		min=(a_set[i]>>10)&63;  max=a_set[i]&1023; pre=(aflags[i]&1023);
		  t=((aflags[i]>>10)&1);  int sence = 1024/pre;  
		Ain=constrain(analogRead(i), min, max );  
		 if (t==0)  Ain = map(Ain, min, max, 0, 1023); 
		 int pos = round(float(Ain)/sence);
				if (A_pos[i] != pos || iscan==1) { A_pos[i] = pos; 
					if (t==0)  pos = constrain(map(pos, 0, pre, 0, 1000), 0, 1000);  
					else pos++;   AIn(i, pos, t);	 
		if (iscan==0 && t==1 ) { atime = millis();  return; }	
			}  }
		atime = millis(); }
}
boolean ReadInput (byte pin, byte act, byte mx) {
if (act==222) { act=2, mx=222; }
if (pin >= d_pins) mx=222;
if (act==2) { if (mx==222) { int a=(pin)/16; int c=pin-(a*16); 
return !bitRead(sim.mxflag[a], c);	}
else { if ((flags[pin]&1)==0) return 0;
return !bitRead(flags[pin], 3); }  }
if (sim.Act != pin || mx!=sim.mxa) return 0;	
if (act==255) act=1;if (sim.active==!act) return 1; return 0; }
byte CountButton (byte pin, byte mode, byte cm) {
if ((flags[pin]&4)==0)  sim.PinSet(pin, 2);
byte cn=(flags[pin]&112)>>4; if (cn==mode) { cn=0; flags[pin]=flags[pin]&143;  }
if (cn+1 == cm && sim.Act == pin)  return 1; else return 0; }
void EncModeBtn(byte pin, byte enc, byte id, byte mx) {
if (mx==0 && (flags[pin]&1)!=0) return; 
if (sim.Emode[enc-1]==0) sim.Emode[enc-1]=id;
if (pin >= d_pins) mx=222;
if (sim.active ==0 || sim.Act != pin || mx!=sim.mxa) return; 
sim.Emode[enc-1]=id;}
boolean NewData(byte idx) { if ((flags[idx]&128)!=0) {  return 1; } else return	0;} 
	float GetData(byte idx) { bitClear(flags[idx], 7); return sim.Dget[idx];}
void SetData(byte idx, float val) {  sim.Dget[idx]=val;  bitSet(flags[idx], 7); }
boolean ARDsim::ToSlave(byte data) {   
if (w_pin!=0 && (flags[w_pin]&7)==0)  { bitSet(flags[w_pin], 1); bitSet(flags[w_pin+1], 1); } 
if ((flags[data]&128)!=0) {   union { byte byte_v[4]; float fl_v; }  ftob;
ftob.fl_v =  Dget[data];   bitClear(flags[data], 7); to_slave[0]=data;
for (int n=0; n<4; n++) to_slave[n+1]=ftob.byte_v[n]; return 1; } return 0; }
void SendToSlave(byte s, byte d0, byte d1, byte d2, byte d3, byte d4 ) {
  if (sim.ToSlave(d0)) SlaveOUT(s); 
  if (d1>0 && sim.ToSlave(d1)) SlaveOUT(s); if (d2>0 && sim.ToSlave(d2)) SlaveOUT(s); 
  if (d3>0 && sim.ToSlave(d3)) SlaveOUT(s); if (d4>0 && sim.ToSlave(d4)) SlaveOUT(s); 
  } 
void GetMaster() { 
union { byte byte_v[4]; float fl_v; }  ftob; 
for (int i=0; i<4; i++) ftob.byte_v[i] = sim.to_slave[i+1];  
sim.Dget[sim.to_slave[0]]=ftob.fl_v;  bitSet(flags[sim.to_slave[0]], 7); }
void LEDout( byte pin, byte dr, float val, float val1, boolean inv) {  
if ((flags[pin]&2)==0) { sim.PinSet(pin, 1); return; }
if (dr == 0)  { digitalWrite(pin, 0);  return; }
if (dr==255)  { digitalWrite(pin, 1); return; }
if ((flags[dr]&128)!=0) {  
if (val1==-999) {
if (sim.Dget[dr] != val) digitalWrite(pin, 0); 
else  digitalWrite(pin, 1); 	} 
else { if (sim.Dget[dr] < val || sim.Dget[dr] > val1) digitalWrite(pin, inv);  
else  digitalWrite(pin, !inv);}	bitClear(flags[dr], 7);  } }
void Gauge (byte num, byte pin, float min, float max, int gmin, int gmax) {
if ((flags[pin]&7)==0) sim.PinSet(pin, 1);
if ((flags[num]&128)==0 || sim.Dget[num]<min || sim.Dget[num]>max) return; // new and in range?
bitClear(flags[num], 7); float c = sim.Dget[num]; int n=1; 
if (abs(max)<1) n=1000;  else if (abs(max)<10) n=100; else if (abs(max)<100) n=10;
max*=n; min*=n;  c*=n;  gmin=256*gmin/100; gmax=256*gmax/100;
c=(c-min)*(gmax-gmin)/(max-min)+gmin; analogWrite (pin, c); }
void servoGauge (byte num, byte pin, float min, float max, int smin, int smax) {
if ((flags[pin]&7)==0) { sim.PinSet(pin, 1); bitSet(flags[num], 7);
sim.snum++;  sim.srvpin[sim.snum]=pin;    return; } int s=0;
if ((flags[num]&128)==0 || sim.Dget[num]<min || sim.Dget[num]>max) return; 
for (int m=0; m<11; m++) { s=m; if (sim.srvpin[m]==pin) break; }
bitClear(flags[num], 7); float c= sim.Dget[num]; int n=1; int lo=smin; int hi=smax; 
if (smax<smin) { lo=smax;  hi=smin;} if (abs(max-min)<=1) n=1000; 
else if (abs(max-min)<20) n=100; else if (abs(max-min)<200) n=10;
max*=n; min*=n;	c=(c*n-min)*(smax-smin)/(max-min)+smin;
if (c>=lo && c<=hi)  sim.sGau[s] = c; }
void ARDsim::Timing() {  unsigned long t=millis()-stime; 
if (t > 19 && snum!=255) {	stime=millis(); if (t<21) {	int sort[20]; int val; byte sn[20];
for (int i=0; i<20; i++) { sort[i]=0; sn[i]=0; }
for (int i=0; i<20; i++) { val = sGau[i];   int n;
for (n=i-1; (n >= 0) && (val < sort[n]); n--) { sort[n+1] = sort[n];	sn[n+1]=sn[n]; }
sort[n+1] = val; sn[n+1]=i;  }	int srvn=19-snum; int h=srvn;
while (h<20) { digitalWrite(srvpin[sn[h]], HIGH);  delayMicroseconds(2);  h++;  }
h=sort[srvn]-((snum-1)*8); delayMicroseconds(h); digitalWrite(srvpin[sn[srvn]], 0); h=srvn+1;
while (h<20) { if (sort[h]>sort[h-1]) delayMicroseconds(sort[h]-sort[h-1]);  
digitalWrite(srvpin[sn[h]], 0);   h++; } }  }	}
//--------------test -
void ARDsim::StepRes() {
for (int s=0; s<10; s++) { 	if (mid[s]!=0) stp_dn(s, 1020);  abspos[s]=0; } }
void StepperGauges() {
if (micros()-sim.inscan > 800) sim.inscan=0;
else if (micros()-sim.inscan < 800) sim.inscan=sim.inscan+(800-sim.inscan);
for (int s=0; s<sim.stn; s++) {
if (sim.mid[s]!=0) { int d=sim.sdref[s]; long val;
if ((flags[d]&128)!=0) { float c = sim.Dget[d]; int n=1; 
if (abs(sim.stmax[s])<2) n=1000; else if (abs(sim.stmax[s])<10) n=100; 
else if (abs(sim.stmax[s])<100) n=10;
long max=sim.stmax[s]*n; long min=sim.stmin[s]*n;  val= long(c*n);  
val = map(val, min, max, 0, 1000);	//	StepPos(s, val);
if (sim.mstep[s]==7) sim.mstep[s]=1; if (sim.mstep[s]==0) sim.mstep[s]=6; 
if (val>sim.abspos[s]) { sim.StepGau(s, sim.mstep[s], 1); sim.mstep[s]++;}
else {  sim.StepGau(s, sim.mstep[s], 0);  sim.mstep[s]--; }  // }
if (val==sim.abspos[s]) bitClear(flags[d], 7);
}   }  }   delayMicroseconds(sim.inscan); }
void StepGauge ( byte A, byte B, byte mid, byte dref, float min, float max ) {
sim.PinSet(A, 1); sim.PinSet(B, 1); sim.PinSet(mid, 1); 
sim.stn++; int s=sim.stn-1;	sim.A_coil[s] = A; sim.mid[s] = mid; sim.B_coil[s] = B;  
sim.sdref[s]=dref; sim.stmin[s]=min; sim.stmax[s]=max; }
void ARDsim::StepGau (byte st, int phase, int dir) {
if (dir==1) abspos[st]++; else abspos[st]--;
if (abspos[st] >=1000  ) return;
switch (phase) {
case 1: digitalWrite(A_coil[st],HIGH); digitalWrite(mid[st],LOW);  digitalWrite(B_coil[st],HIGH);  break;
case 2: digitalWrite(A_coil[st],HIGH); digitalWrite(mid[st],LOW);  digitalWrite(B_coil[st],LOW);  break;
case 3: digitalWrite(A_coil[st],HIGH); digitalWrite(mid[st],HIGH); digitalWrite(B_coil[st],LOW);  break;
case 4: digitalWrite(A_coil[st],LOW);  digitalWrite(mid[st],HIGH); digitalWrite(B_coil[st],LOW);  break;
case 5: digitalWrite(A_coil[st],LOW);  digitalWrite(mid[st],HIGH); digitalWrite(B_coil[st],HIGH);  break;
case 6: digitalWrite(A_coil[st],LOW);  digitalWrite(mid[st],LOW);  digitalWrite(B_coil[st],HIGH);  break;  
  }   }
void StepPos (byte st, int pos) {   //set position
while (pos!=sim.abspos[st]) { delayMicroseconds(800);
if (sim.mstep[st]==7) sim.mstep[st]=1; if (sim.mstep[st]==0) sim.mstep[st]=6; 
if (pos>sim.abspos[st]) { sim.StepGau(st, sim.mstep[st], 1); sim.mstep[st]++;}
else {  sim.StepGau(st, sim.mstep[st], 0);  sim.mstep[st]--; }   }  }
void ARDsim::stp_dn(byte st, int val) {
while (val!=0) { delayMicroseconds(800);
if (mstep[st]==0) mstep[st]=6; 
StepGau(st, mstep[st], 0);  mstep[st]--; val--;  }  }
void ARDsim::stp_up(byte st, int val) {
while (val!=0)  {  delayMicroseconds(800);
if (mstep[st]==7) mstep[st]=1; 
StepGau(st, mstep[st], 1); mstep[st]++; val--; }  }
void ARDsim::Comm() { 
xData(1); 	if (ps>3) {
if (lan==1) { xData(7, ps); db[ps]='\0';  
if (db[0]==88) { if (db[1]==80) { for (byte i=0; i<6; i++) conf[i]=db[2+i];  iscan=1;  ArdInit(); } 
if (db[1]==88 &&  iscan==1) { for (byte i=0; i<6; i++) conf[i]=db[2+i];  } 		}
else if (db[0] == 62) { int pos=1;  byte dref_ID;  char Data_read[8];   
while (pos < ps) {  dref_ID = db[pos];  pos+=2; int n=0;   
while (db[pos] != 62) { Data_read[n] = db[pos];  pos++;  n++;  }  
Data_read[n]='\0';  Dget[dref_ID]=atof(Data_read); bitSet(flags[dref_ID], 7);  pos++; }  }   } 	
else {  int c=ps-1;  int ms=ps; db[0]=xData(6); 
if (db[0]!=62) { for (int a=1; a<ps; a++) { xData(6); if (inx==60)  return;  } return; }
else {	for (int i=1; i<ps; i++)  db[i]=xData(6);
if (db[ps-1]!=60) {  while (db[ms-1]!=60) {  xData(1);
if (ps>0) {  for (int i=ms; i<ps+ms; i++) { db[i]=xData(6);  }
ms+=ps; }  }  }
if (db[1]==254) { inits='+'; for (byte i=0; i<6; i++) conf[i]=db[i+2]; 
if (db[8]=='-') iscan=1; return; } c=0;   byte dref_ID;  char Dread[8];  
while (c < ms) { c++; dref_ID = db[c]; c++; int n=0;   
while (db[c]!=60) { Dread[n] = db[c];  c++; n++;  } Dread[n]='\0';  		
Dget[dref_ID]=atof(Dread); bitSet(flags[dref_ID], 7); c++; }
for (int i=0; i<64; i++) db[i] = 0; } ps=0; } }}
void ARDsim::ArdInit() {  xData(4, '>'); SendPack(ardn, 4);  xData(4, '<');  }
void ARDsim::SClr() {  if (xData(1)>0) for (int i=0; i<ps; i++) xData(6); }
void ARDsim::SendPack(char* str, byte num) { for (int i=0; i<num; i++) xData(2,str[i]); }
void ARDsim::Send(byte type, int num, byte dir, byte mode) { 
byte b; byte c; byte a = num /100;  
if (a!=0) num=num-a*100; b=num /10;
if (b!=0) num=num-b*10; c=num;
xData(4, '>'); xData(2, conf[5]);  xData(2, sim.ARD); xData(2, conf[type]);
if (a>0) xData(2, a+48);  if (b>0 || a>0) xData(2, b+48); 	xData(2, c+48); 
if (mode>0) { xData(2, '/'); if (mode<65) mode+=48; xData(2, mode); } 
if (dir>0) xData(2, 41+dir*2); 	xData(4, '<'); } 
void SimInput(byte num) { if (sim.start==0) return; sim.Send(4,num); }	
void ARDsim::AIn(byte num,  int val, byte t) { 	if (sim.start==0) return;	
byte b; byte a = num /10;  	itoa(val, value, 10); 
if (a!=0) num=num-a*10; b=num;	byte d; byte c = val /10; 
if (c!=0) val=val-c*10; d=val;
xData(4, '>');  xData(2, conf[5]); xData(2, ARD); xData(2, conf[2]) ; 
if (a>0) xData(2, a+48); xData(2, b+48); 
if (t==1) { xData(2, '/'); if (c>0) xData(2, c+48);
xData(2, d+48); } else { xData(2, ' '); xData(3); }
xData(4, '<'); }
void XPDref (char* DRef, float Val) {  }
void XPCmnd (char* Com) {  }
void XPMenu (int MenuNum)  {  }


