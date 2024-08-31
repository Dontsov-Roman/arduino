#include <GpsCar.h>
#include <SoftwareSerial.h>
#include <GpsReader.h>
#include <WifiHttpClient.h>
#include <SimpleOled.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SimpleOled simpleOled(&display);

#ifndef STASSID
// #define STASSID "car_wifi"
#define STASSID "56"
#define STAPSK "dontsovaAlya"
// #define HOST "100.64.37.15"
#define HOST "192.168.0.104"
#define PORT "80"
#define URL "/set-gps"
#endif

const char* wifiSsid = STASSID;
const char* wifiPassword = STAPSK;
const char* host = HOST;
const char* port = PORT;
const char* url = URL;

SoftwareSerial ss(D4, D3);
GpsReader gpsReader(&ss);
WifiHttpClient wifiHttpClient(wifiSsid, wifiPassword, host, url, port);
GpsCar gpsCar(&gpsReader, &wifiHttpClient, &simpleOled);

void setup() {
  Serial.begin(115200);
  ss.begin(9600);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
  }

  gpsCar.begin();
}

void loop() {
  gpsCar.loop();
}
