#ifndef LVGL_ESP_32
#define LVGL_ESP_32
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <lvgl.h>

#include <SimpleTimeout.h>
#include <IHttpClient.h>
#include <IWifiClient.h>
#include <GpsData.h>
#include <NtpTime.h>
#include <OpenWeather.h>
#include <WeatherTileLvgl.h>
#include <ArduinoJson.h>

class HomeLvgl
{
private:
    SimpleTimeout reconnectionTimeout = SimpleTimeout(10000);
    SimpleTimeout renderTimeout = SimpleTimeout(15000);
    SimpleTimeout getGpsTimeout = SimpleTimeout(30000);
    SimpleTimeout buttonTimeout = SimpleTimeout(500);
    GpsData gpsData;

    int weatherTileCount = 6;
    WeatherTileLvgl weatherTile[6];
    IWifiClient *wifiClient;
    IHttpClient *gpsHttpClient;
    NtpTime *ntpTime;
    OpenWeather *openWeather;

    String turnOnLightUrl = "/led/1";
    String turnOffLightUrl = "/led/0";
    // Flex style
    lv_style_t style;
    // Tabs
    lv_obj_t *tabs;
    lv_obj_t *homeTab;
    // lv_obj_t *gpsTab;
    lv_obj_t *weatherTab;
    // Tabs content
    lv_obj_t *createTabContent(lv_obj_t *parent);
    lv_obj_t *homeContent;
    lv_obj_t *gpsContent;
    lv_obj_t *weatherContent;

    // labels
    lv_obj_t *homeTimeLabel;
    lv_obj_t *gpsTimeLabel;
    lv_obj_t *gpsCoordsLabel;

    void createHomeEntities(lv_obj_t *parent);
    void createGpsEntities(lv_obj_t *parent);
    void createWeatherEntities();
    void render();
    void renderWeatherTiles();

    // Button events
    void turnOnLight(lv_event_t *e);
    void turnOffLight(lv_event_t *e);

    template <void (HomeLvgl::*Method)(lv_event_t *)>
    static void eventThunk(lv_event_t *e)
    {
        auto self = static_cast<HomeLvgl *>(lv_event_get_user_data(e));
        if (self)
        {
            (self->*Method)(e);
        }
    }

public:
    HomeLvgl(
        IWifiClient *wifiClient,
        IHttpClient *gpsHttpClient,
        NtpTime *ntpTime,
        OpenWeather *openWeather);
    void begin();
    void loop();
    int getWeatherTileCount();
};
#endif