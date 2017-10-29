#include "ArdCom.h"
void ArdCom::StPos (byte s) {	
int fs=stm[s];  rst[0][s]-=cy; 
if (rst[0][s]<1) { if (rst[1][s]>0) { DOUT(conf[7],HIGH); rst[3][s]++;  if (rst[3][s]==fs) rst[3][s]=0;  } 
else { DOUT(conf[7],LOW); rst[3][s]--;  if (rst[3][s]==-1 && rst[2][s]>0) rst[3][s]=fs-1; }	
STEP if (rst[2][s]!=rst[3][s]) {  rst[0][s]=abs(rst[1][s]); } else { rst[1][s]=0;  } } }
void ArdCom::S_set() {  unsigned long t=millis()-stime; 
if (t > 19) { stime=millis(); if (t<25) { int sort[10]; int val; byte sn[10];  int n;
for (int i=0; i<10; i++) { sort[i]=0; sn[i]=0; }
for (int i=0; i<10; i++) { val = sGau[i]; 
for (n=i-1; (n >= 0) && (val < sort[n]); n--) { sort[n+1] = sort[n];	sn[n+1]=sn[n]; }
sort[n+1] = val; sn[n+1]=i; } int srvn=9-snum; int h=srvn;
while (h<10) { DOUT(srvpin[sn[h]], HIGH);  DMS(2);  h++;  }
h=sort[srvn]-((snum-1)*8);   DMS(h); DOUT(srvpin[sn[srvn]], 0); h=srvn+1;
while (h<10) { if (sort[h]>sort[h-1]) DMS(sort[h]-sort[h-1]);  
DOUT(srvpin[sn[h]], 0);   h++; } } } }
void ArdCom::SimGet(int mode) {  
int pos=0;   byte in;  xData(1); 
if (ps>1) {	if (mode==1) { xData(6);
if (inx!=126) return; 
for (int s=7; s<12; s++) conf[s]=100; if (ucom) { do xData(1); while (ps<60); } 
for (int n=0; n<54; n++) { xData(6);  
if (inx>0 && n<d_pins) { ModeSet(n, inx); 
if (inx==5) { if (conf[8]==conf[9]) conf[8]=n; else conf[9]=n;}
if (inx==6) { if (conf[10]==conf[11]) conf[10]=n; else conf[11]=n;}	}}
for (int i=0; i<6; i++) { conf[i]=xData(6);  }
prtCom('a',1,0); int pin=0; delay(500); 
if (ucom) { do xData(1); while (ps<49); }  xData(1);	 
if (xData(6)==65) { while (pin<inp.a_pins) {  inp.aflags[pin]=xData(6); 
inp.a_min[pin]=xData(6); inp.a_max[pin]=xData(6); 
if (inp.aflags[pin]==1) ModeSet(pin, 'D'); 
if (inp.aflags[pin]==2) ModeSet(pin, 'O'); 	pin++;  } }
prtCom(RES); byte h; byte l; int t=0;	prtCom('s',1,0);  delay(500); 
if (ucom) { do xData(1); while (ps<2); } xData(1); 
if (xData(6)==83) { ps=0; t=0; pos = xData(6); 
if (ucom && ps<pos) { do xData(1); while (ps<pos); }
while (t<pos) { in=xData(6); l=xData(6); h=xData(6); stm[in] = l + (h<<8); t+=3; }} 
prtCom(RES); start=1;}
else { in=xData(6);
if (in==123 ) { union{ byte bv[4]; float fv;} bf;  
ps=0; byte dev; byte n=0; byte bnum = xData(6);  
if (ucom && ps<bnum) { while (ps<bnum) xData(1); }	// wait all sd // prtCom('x', 1, 0);  //restrict
n=xData(6); int st=1; if (n<54) {  
while (pos < bnum) { if (st==0) n=xData(6); st=0; pos++; dev=xData(6);  pos++;  
if (dev==73) { to_slave[0]=n; for (int c=1; c<5; c++) to_slave[c]=xData(6); SlaveOUT(); pos+=4; } // to slv
else if (dev<42) DOUT(n, dev-40);		       
else if (dev==80) { analogWrite (n, xData(6));	 pos++; }  
else if (dev==82) { byte r; byte nb=xData(6);  pos++; 
byte p = conf[12]; byte l = conf[13]; 
for (int i=0; i<nb; i++) { r=xData(6); pos++; for (int x=0; x<8; x++) REGS } REGW }
else { 	for (int c=0; c<4; c++) { bf.bv[c] = xData(6); pos++; } // -- din
if (dev==68) ProgOut(n, bf.fv);	else if (dev==83) { rtime=millis();
for (byte s=0; s<10; s++) { if (srvpin[s]==n) sGau[s]=int(bf.fv); } }
else if (dev==71) {	word parl = bf.bv[0]+(bf.bv[1]<<8); word parh = bf.bv[2]+(bf.bv[3]<<8);  
rst[2][n]=int(parl);  int ph=int(parh);    int fs=stm[n];
byte mod=flags[n]&15;    int dv=rst[2][n]-rst[3][n];  
if (dv!=0) {  if (mod==10) {
if (dv<0 && dv< -fs/1.2) dv=fs+dv;	else if (dv>0 && dv>fs/1.2) dv=dv-fs; }
rst[1][n]= constrain(abs((ph*10)/dv), 300, 32760);
if (dv<0) rst[1][n]*=-1;  rst[0][n]=abs(rst[1][n]); } } } } }
else {  }  // res
}//----------------  ext res------------
else if (in==88) { byte id=xData(6); 	//	start=0;
if (id==80) SimReset(0); else if (id==82) SimReset(1);	} 	//-- recon, reset 
else  if (in=='D')  { xData(7, ps-1);  for (int i=5; i<ps-1; i++) { }  }  //?
//		prtCom(RES); 	// prtCom('w', 1, 0); 	 //test	
}} }
void ArdCom::prtCom(byte type, byte in, int dv) {
if(type==100) { xData(1); for (int i=0; i<ps; i++)  xData(6); return; }
byte a;  byte cfg;  byte key=conf[5]; int r=2;	if (type==2 || type==4) r=0; 
else if (type==5) { r=1; type=2; } 	else if (type==6) type=2; 
if (type<5) cfg=conf[type]; else cfg=type;	xData(4); 
if (type<5) xData(2, key); xData(2, ARD); xData(2,cfg); 
if (in>99) { a=in/100; in=in-a*100; xData(2, a+48); a=in/10; xData(2, a+48); in=in-a*10; }
else if (in>9) { a=in/10; xData(2, a+48); in=in-a*10; }
xData(2, in+48); if (r==0) {  xData(2, ' '); xData(3); 
if (com.rm[0]=='.') { for (int j=0; j<5; j++) xData(2, rm[j]); com.rm[0]=0; } }  //-			
else if (r==1) { xData(2, '/');  xData(2, dv+48); }   
else { if (dv>0) xData(2, 41+dv*2); }  xData(5); } 
void SlaveWrite(int num, float val) { union { byte byte_v[4]; float fl_v; } ftob;
ftob.fl_v =  val; com.to_slave[0]=num;
for (int n=1; n<5; n++) com.to_slave[n]=ftob.byte_v[n-1]; SlaveOUT(); }
void ArdCom::SimReset(byte r) {  prtCom('x', 1, 0); 
if (r==0) { start=0; for (int i=0; i<d_pins; i++) flags[i]=0;  
for (int t=0; t<14; t++) conf[t]=0; while(start==0) { 
prtCom(RES); delay(1000); xData(4); 
xData(2, '|'); xData(2, 'A'); xData(2, 'R'); xData(2, char(ARD+48));
xData(5); delay(300); SimGet(1); delay(300);
} if (conf[7]<100) StRes();  }
Scan(1);  prtCom('w', 1, 0);  }
byte  ArdCom::xData(byte n, int d) {
if (ucom) { switch(n) { 
case 1: ps=Serial.available(); return ps; break; case 2: SW(d);  break; 
case 3: SW(dfv); dfv[4]=0; break; case 4: SW(123); break; case 5: SW(125); break; 
case 6: inx=Serial.read(); return inx; break;  } return 0; }
else return XData(n, d); }
void ArdCom::StRes() {
//pinMode(2, OUTPUT); digitalWrite(2,HIGH);
//digitalWrite(2,LOW); digitalWrite(2,HIGH); delayMicroseconds(500); 	//temp
DOUT(conf[7],LOW); delay(100); 	int stn=0;  int st;  
for (byte s = 0; s < d_pins; s++)  { st=flags[s]&15;  rst[3][s]=0;
if (st==9 || st==10) { rst[3][s]=stm[s]; stn++; } }
while (stn!=0) { delayMicroseconds(300); 
for (byte s = 0; s < d_pins; s++)  { st=flags[s]&15; 
if (rst[3][s]!=0) {	if (st==9) { STEP  rst[3][s]--; if (rst[3][s]==0) stn--; }
else if (st==10) { if (digitalRead(s+1)!=0) { STEP } else { rst[3][s]=0; stn--; } } } }	}
//digitalWrite(2,LOW); digitalWrite(2,HIGH); delayMicroseconds(500); 
}
ArdCom::ArdCom() { }
ArdCom com = ArdCom();
