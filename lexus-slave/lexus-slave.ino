#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

Servo servo1;
const int pinServo = 6; // пин для подключения сервопривода
const int IN1 = 8, IN2 = 4, ENA = 3, IN3 = 7, IN4 = 5;

RF24 radio(9, 10); // Создаём объект radio   для работы с библиотекой RF24, указывая номера выводов nRF24L01+ (CE, CSN)

int data[3],
    thorttle = 0;

int steer, trle, light;
void setup() {
  Serial.begin (9600);
  pinMode (ENA, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);

  servo1.attach(pinServo);
  radio.begin();                                        // Инициируем работу nRF24L01+
  radio.setChannel(5);                                  // Указываем канал приёма данных (от 0 до 127), 5 - значит приём данных осуществляется на частоте 2,405 ГГц (на одном канале может быть только 1 приёмник и до 6 передатчиков)
  radio.setDataRate     (RF24_1MBPS);                   // Указываем скорость передачи данных (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1Мбит/сек
  radio.setPALevel      (RF24_PA_HIGH);                 // Указываем мощность передатчика (RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBm, RF24_PA_MAX=0dBm)
  radio.openReadingPipe (1, 0x1234567890LL);            // Открываем 1 трубу с идентификатором 0x1234567890 для приема данных (на ожном канале может быть открыто до 6 разных труб, которые должны отличаться только последним байтом идентификатора)
  radio.startListening  ();                             // Включаем приемник, начинаем прослушивать открытую трубу
  // radio.stopListening   ();                          // Выключаем приёмник, если потребуется передать данные

  servo1.write(90);
}

void loop() {
  delay(50);
  if (radio.available()) {
    radio.read(&data, sizeof(data));
    steer = data[0];
    trle = data[1];
    light = data[2];

    servo1.write(steer);
    thorttle = map(trle, 0, 1023, -300, 300);
    analogWrite(ENA, abs(constrain(thorttle - 96, -200, 200)));

    Serial.println(constrain(thorttle - 110, -200, 200));

    if (thorttle > 0) {
      digitalWrite (IN1, LOW);
      digitalWrite (IN2, HIGH);
    } else {
      digitalWrite (IN1, HIGH);
      digitalWrite (IN2, LOW);
    }
  }
}
