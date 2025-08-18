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
#include <WeatherTabLvgl.h>
#include <ArduinoJson.h>

class HomeLvgl
{
private:
    SimpleTimeout reconnectionTimeout;
    SimpleTimeout renderTimeout;
    SimpleTimeout getGpsTimeout;
    GpsData gpsData;

    WeatherTabLvgl weatherTile[3];
    IWifiClient *wifiClient;
    IHttpClient *gpsHttpClient;
    NtpTime *ntpTime;
    OpenWeather *openWeather;

    String turnOnLightUrl = "/led/1";
    String turnOffLightUrl = "/led/0";
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
    lv_obj_t *temperatureLabel;
    lv_obj_t *weatherDescriptionLabel;

    void createHomeEntities(lv_obj_t *parent);
    void createGpsEntities(lv_obj_t *parent);
    void createWeatherEntities(lv_obj_t *parent);
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
};
#endif