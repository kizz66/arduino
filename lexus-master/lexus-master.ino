#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int ledPin = 13;
RF24 radio(9, 10); // Создаём объект radio для работы с библиотекой RF24, указывая номера выводов nRF24L01+ (CE, CSN)
int data[3];
int button = 4;

void setup() {
  pinMode(button, INPUT);
  
  radio.begin();                                        // Инициируем работу nRF24L01+
  radio.setChannel(5);                                  // Указываем канал передачи данных (от 0 до 127), 5 - значит передача данных осуществляется на частоте 2,405 ГГц (на одном канале может быть только 1 приёмник и до 6 передатчиков)
  radio.setDataRate     (RF24_1MBPS);                   // Указываем скорость передачи данных (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1Мбит/сек
  radio.setPALevel      (RF24_PA_HIGH);                 // Указываем мощность передатчика (RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBm, RF24_PA_MAX=0dBm)
  radio.openWritingPipe (0x1234567890LL);               // Открываем трубу с идентификатором 0x1234567890 для передачи данных (на одном канале может быть открыто до 6 разных труб, которые должны отличаться только последним байтом идентификатора)
}

void loop() {
  data[0] = map(analogRead(A1), 0, 1023, 0, 180);
  data[1] = map(analogRead(A2), 0, 1023, 0, 180);
  data[2] = digitalRead(button);
  radio.write(&data, sizeof(data));                     // отправляем данные из массива data указывая сколько байт массива мы хотим отправить. Отправить данные можно с проверкой их доставки: if( radio.write(&data, sizeof(data)) ){данные приняты приёмником;}else{данные не приняты приёмником;}
  delay(50);
}
