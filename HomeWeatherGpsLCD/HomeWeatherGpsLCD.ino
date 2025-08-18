#include <Arduino.h>
// #include <esp_display_panel.hpp>

#include <lvgl.h>
#include "lvgl_v8_port.h"

#include <WifiClientEsp32.h>
#include <HttpClientEsp32.h>
#include <LvglEsp32.h>

using namespace esp_panel::drivers;
using namespace esp_panel::board;

#ifndef STASSID
// #define STASSID "UFI-495947"
// #define STAPSK "12345678"
// #define STASSID "car_wifi"
#define STASSID "56"
#define STAPSK "dontsovaAlya"
#define HOST "195.78.246.46"
#define PORT "8080"
#define URL "/get-gps"
#define NTP_SERVER "pool.ntp.org"
#define GMT_OFFSET 7200
#define DAY_LIGHT_OFFSET 3600
#define OPEN_WEATHER_API_KEY "9a77f4e52681be3d74817619d3689c73"
#define OPEN_WEATHER_HOST "api.openweathermap.org"
#define OPEN_WEATHER_PORT "80"
#define OPEN_WEATHER_URL "data/2.5/forecast"
#define OPEN_WEATHER_LAT "46.403395"
#define OPEN_WEATHER_LNG "30.721698"
#endif

const char *wifiSsid = STASSID;
const char *wifiPassword = STAPSK;
const char *host = HOST;
const char *port = PORT;
const char *url = URL;
const char *ntpServer = NTP_SERVER;
const long gmtOffset = GMT_OFFSET;
const int dayLightOffset = DAY_LIGHT_OFFSET;

const char *openWeatherHost = OPEN_WEATHER_HOST;
const char *openWeatherUrl = OPEN_WEATHER_URL;
const char *openWeatherPort = OPEN_WEATHER_PORT;
const char *openWeatherApiKey = OPEN_WEATHER_API_KEY;
char *openWeatherLat = OPEN_WEATHER_LAT;
char *openWeatherLng = OPEN_WEATHER_LNG;

SimpleTimeout ntpTimer(30000);

WifiClientEsp32 wifiClient(wifiSsid, wifiPassword);
HttpClientEsp32 httpClient(host, url, port);
NtpTime ntpTime(&ntpTimer, ntpServer, gmtOffset, dayLightOffset);

LvglEsp32 mylvgl(&wifiClient, &httpClient, &ntpTime);
void setup()
{
    Serial.begin(115200);
    wifiClient.begin();

    Serial.println("Initializing board");
    Board *board = new Board();
    board->init();

#if LVGL_PORT_AVOID_TEARING_MODE
    auto lcd = board->getLCD();
    // When avoid tearing function is enabled, the frame buffer number should be set in the board driver
    lcd->configFrameBufferNumber(LVGL_PORT_DISP_BUFFER_NUM);
#if ESP_PANEL_DRIVERS_BUS_ENABLE_RGB && CONFIG_IDF_TARGET_ESP32S3
    auto lcd_bus = lcd->getBus();
    /**
     * As the anti-tearing feature typically consumes more PSRAM bandwidth, for the ESP32-S3, we need to utilize the
     * "bounce buffer" functionality to enhance the RGB data bandwidth.
     * This feature will consume `bounce_buffer_size * bytes_per_pixel * 2` of SRAM memory.
     */
    if (lcd_bus->getBasicAttributes().type == ESP_PANEL_BUS_TYPE_RGB)
    {
        static_cast<BusRGB *>(lcd_bus)->configRGB_BounceBufferSize(lcd->getFrameWidth() * 10);
    }
#endif
#endif
    assert(board->begin());

    Serial.println("Initializing LVGL");
    lvgl_port_init(board->getLCD(), board->getTouch());

    Serial.println("Creating UI");
    /* Lock the mutex due to the LVGL APIs are not thread-safe */
    lvgl_port_lock(-1);
    mylvgl.begin();
    lvgl_port_unlock();
}

void loop()
{
    // Serial.println("IDLE loop");
    mylvgl.loop();
    delay(1000);
}
