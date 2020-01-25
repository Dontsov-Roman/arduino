
#include "UTFT.h"
// библиотека для работы с дисплеем
// создаём объект класса UTFT
// и передаём идентификатор модели дисплея и номера управляющих пинов
UTFT myGLCD(ILI9486, 38, 39, 40, 41);
// объявления встроенного шрифта
extern uint8_t BigFont[];

void setup()
{
  Serial.begin(9600);
  // инициализируем дисплей
  myGLCD.InitLCD();
  // очищаем экран
  myGLCD.clrScr();
  // выбираем тип шрифта
  myGLCD.setFont(BigFont);
  // печатаем «Hello, world!» в центре верхней строки дисплея
  myGLCD.print("Hello, world!", CENTER, 0);
}
void loop()
{
  Serial.print("TEST");
  delay(1000);
}
