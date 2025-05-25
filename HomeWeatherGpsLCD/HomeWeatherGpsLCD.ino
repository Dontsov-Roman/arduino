#include <Arduino_GFX_Library.h>
#include <Arduino_GFX.h>

// Определение пинов подключения
#define LCD_R0 4
#define LCD_R1 5
#define LCD_R2 6 //LCD_G??
#define LCD_R3 7
#define LCD_R4 15

#define LCD_G0 16
#define LCD_G1 17
#define LCD_G2 18
#define LCD_G3 8
#define LCD_G4 3
#define LCD_G5 46

#define LCD_B0 9
#define LCD_B1 10
#define LCD_B2 11
#define LCD_B3 12
#define LCD_B4 13

#define LCD_CLK 14
#define LCD_DISP 21

#define LCD_HSYNC 47
#define LCD_VSYNC 48
#define LCD_DE 40
#define BL_EN 45

// Тайминги из даташита или отладки
#define H_RES 480
#define V_RES 272

// Инициализация панели
// Arduino_ESP32RGBPanel *rgbPanel = new Arduino_ESP32RGBPanel(
//     TFT_DE, TFT_VSYNC, TFT_HSYNC, TFT_PCLK,
//     TFT_R0, TFT_R1, TFT_R2, TFT_R3, TFT_R4,
//     TFT_G0, TFT_G1, TFT_G2, TFT_G3, TFT_G4, TFT_G5,
//     TFT_B0, TFT_B1, TFT_B2, TFT_B3, TFT_B4,
//     1, 40, 48, 40, // HSYNC: polarity, front porch, pulse width, back porch
//     1, 13, 3, 32,  // VSYNC: polarity, front porch, pulse width, back porch
//     0, 6000000L, false, 480, 272);
Arduino_ESP32RGBPanel *rgbPanel = new Arduino_ESP32RGBPanel(
    LCD_DE,
    LCD_VSYNC,
    LCD_HSYNC,
    LCD_CLK,
    // RED
    LCD_R0,
    LCD_R1,
    LCD_R2,
    LCD_R3,
    LCD_R4,
    // GREEN
    LCD_G0,
    LCD_G1,
    LCD_G2,
    LCD_G3,
    LCD_G4,
    LCD_G5,
    // BLUE
    LCD_B0,
    LCD_B1,
    LCD_B2,
    LCD_B3,
    LCD_B4,

    1, 40, 48, 40, // HSYNC: polarity, front porch, pulse width, back porch
    1, 13, 3, 32,  // VSYNC: polarity, front porch, pulse width, back porch
    1, 6000000L, false, 480, 272);
// Инициализация дисплея
Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
    480, 272,                     // ширина, высота
    rgbPanel,                     // RGB-интерфейс
    0,              // uint8_t r
    false,                        // bool auto_flush,
    NULL,                         // Arduino_DataBus *bus
    LCD_DISP,              // int8_t rst
    st7701_type5_init_operations, // Инициализация ST7701
    sizeof(st7701_type5_init_operations));
void setup()
{

  pinMode(BL_EN, OUTPUT);
  digitalWrite(BL_EN, HIGH);
  gfx->begin();

  gfx->fillScreen(RGB565_RED);

  gfx->setCursor(10, 10);
  gfx->setTextColor(RGB565_WHITE);
  gfx->setTextSize(6);
  gfx->println("Hello, World!");
}

void loop()
{
  // Основной цикл
}
