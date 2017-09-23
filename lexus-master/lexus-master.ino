#include <Wire.h>
#include <SPI.h>
#include <Encoder.h>
#include <MapEncoder.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <AnalogButtonTrigger.h>

const int CLK_PIN = 3;
const int DT_PIN = 4;
const int THORTTLE_PIN = 0;
const int BUTTON_PIN = 2;// button read by analog input A2

int data[3], oldButton = LOW, newButton = LOW;
long oldPosition  = 90;
long oldThorttle  = 0;
long newPosition;
long newThorttle;

RF24 radio(9, 10); // Создаём объект radio для работы с библиотекой RF24, указывая номера выводов nRF24L01+ (CE, CSN)
MapEncoder encoder(3, 4);
AnalogButtonTrigger triggerButton = AnalogButtonTrigger(BUTTON_PIN);

void setup() {
  //Serial.begin (9600);
  radio.begin();                                        // Инициируем работу nRF24L01+
  radio.setChannel(5);                                  // Указываем канал передачи данных (от 0 до 127), 5 - значит передача данных осуществляется на частоте 2,405 ГГц (на одном канале может быть только 1 приёмник и до 6 передатчиков)
  radio.setDataRate     (RF24_1MBPS);                   // Указываем скорость передачи данных (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1Мбит/сек
  radio.setPALevel      (RF24_PA_HIGH);                 // Указываем мощность передатчика (RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBm, RF24_PA_MAX=0dBm)
  radio.openWritingPipe (0x1234567890LL); // Открываем трубу с идентификатором 0x1234567890 для передачи данных (на одном канале может быть открыто до 6 разных труб, которые должны отличаться только последним байтом идентификатора)
  encoder.setScale(50, 130, 90, 1); // серво управления передними колесами
}

void loop() {
  newPosition = encoder.getValue();
  newThorttle = analogRead(THORTTLE_PIN);
  newButton = triggerButton.check();
  
  if (newPosition != oldPosition || newThorttle != oldThorttle || oldButton != newButton) {
    oldPosition = newPosition;
    oldThorttle = newThorttle;
    oldButton = newButton;

    data[0] = oldPosition;
    data[1] = oldThorttle;
    data[2] = oldButton;
    radio.write(&data, sizeof(data));
  }
  delay(10);
}
