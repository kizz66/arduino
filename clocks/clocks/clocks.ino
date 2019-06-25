/*
*/

#define DEC_HOURS 8
#define HOURS 7 //ок
#define DEC_MIN 9 // ok
#define MIN 6

#define D1 10
#define D2 12 // ok
#define D3 11 // ок
#define D4 13 // ok

void setup() {
  pinMode(DEC_HOURS, OUTPUT);
  pinMode(HOURS, OUTPUT);
  pinMode(DEC_MIN, OUTPUT);
  pinMode(MIN, OUTPUT);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);


  digitalWrite(DEC_HOURS, HIGH);
  digitalWrite(HOURS, HIGH);
  digitalWrite(DEC_MIN, HIGH);
  digitalWrite(MIN, HIGH);

  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
}

// the loop function runs over and over again forever
void loop() {
  delay(1000);
  //1
  digitalWrite(D1, HIGH);
  delay(1000);
  digitalWrite(D1, LOW);
  //2
  digitalWrite(D2, HIGH);
  delay(1000);
  digitalWrite(D2, LOW);
  //3
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  delay(1000);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  //4
  digitalWrite(D3, HIGH);
  delay(1000);
  digitalWrite(D3, LOW);
  //5
  digitalWrite(D3, HIGH);
  digitalWrite(D1, HIGH);
  delay(1000);
  digitalWrite(D3, LOW);
  digitalWrite(D1, LOW);
  //6
  digitalWrite(D3, HIGH);
  digitalWrite(D2, HIGH);
  delay(1000);
  digitalWrite(D3, LOW);
  digitalWrite(D2, LOW);
  //7
  digitalWrite(D3, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D1, HIGH);
  delay(1000);
  digitalWrite(D3, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D1, LOW);
  //8
  digitalWrite(D4, HIGH);
  delay(1000);
  digitalWrite(D4, LOW);
  //9
  digitalWrite(D4, HIGH);
  digitalWrite(D1, HIGH);
  delay(1000);
  digitalWrite(D4, LOW);
  digitalWrite(D1, LOW);
}
