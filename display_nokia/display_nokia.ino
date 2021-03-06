// 84 x 48
// Подключение библиотеки
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
// PIN 7 - RST Pin 1 on LCD
// PIN 6 - CE Pin 2 on LCD
// PIN 5 - DC Pin 3 on LCD
// PIN 4 - DIN Pin 4 on LCD
// PIN 3 - CLK Pin 5 on LCD
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 6, 7);

const unsigned char PROGMEM img [] = {
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x1, 0xff, 0x80, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x3, 0xff, 0xc0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0xf, 0xff, 0xe0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x1f, 0xff, 0xf8, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x3f, 0xff, 0xfc, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x7f, 0xff, 0xfc, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xfe, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xfe, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x1, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x1, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x3, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x3, 0xff, 0xff, 0xff, 0x80, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x7, 0xff, 0xff, 0xff, 0x80, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x7, 0xff, 0xff, 0xff, 0x80, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x7, 0xff, 0xff, 0xff, 0x80, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0xf, 0xff, 0xff, 0xff, 0x80, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0xf, 0xff, 0xff, 0xff, 0x80, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0xf, 0xff, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0xf, 0xff, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0xf, 0xff, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0xf, 0xff, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0xf, 0xff, 0xff, 0xff, 0xe0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0xf, 0xff, 0xff, 0xff, 0xe0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0xf, 0xff, 0xff, 0xff, 0xe0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x7, 0xff, 0xff, 0xff, 0xf0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x7, 0xff, 0xff, 0xff, 0xf0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x7, 0xff, 0xff, 0xff, 0xe0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x7, 0xff, 0xff, 0xff, 0xe0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x3, 0xff, 0xff, 0xff, 0xe0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x3, 0xff, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x1, 0xff, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0x80, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x7f, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x7f, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x7f, 0xff, 0xff, 0xf0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x7f, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0x80, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x80, 0x0, 0x0,
  0x0, 0x0, 0x1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x0, 0x0,
  0x0, 0x0, 0x3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x0, 0x0,
  0x0, 0x0, 0xf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x0, 0x0
};

void setup()
{
  display.begin();
  display.cp437(true);
  // установить контраст фона экрана
  // очень важный параметр!
  display.setContrast(60);
  display.clearDisplay(); // очистить экран

  display.drawBitmap(0, 0, img, 84, 48, BLACK);
  //  display.setTextSize(1); // размер шрифта
  //  display.setCursor(0, 0); // позиция курсора
  //  display.setTextColor(BLACK);
  display.print(utf8rus("Кот обормот"));
  //  display.drawLine(0, 0, 100, 100, BLACK);
  display.display();
}
void loop()
{


  delay(1000);
}
/* Recode russian fonts from UTF-8 to Windows-1251 */
String utf8rus(String source)
{
  int i, k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };

  k = source.length(); i = 0;

  while (i < k) {
    n = source[i]; i++;

    if (n >= 0xC0) {
      switch (n) {
        case 0xD0: {
            n = source[i]; i++;
            if (n == 0x81) {
              n = 0xA8;
              break;
            }
            if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
            break;
          }
        case 0xD1: {
            n = source[i]; i++;
            if (n == 0x91) {
              n = 0xB8;
              break;
            }
            if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
            break;
          }
      }
    }
    m[0] = n; target = target + String(m);
  }
  return target;
}

