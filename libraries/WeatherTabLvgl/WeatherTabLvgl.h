#ifndef WEATHER_TAB_LVGL
#define WEATHER_TAB_LVGL
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <lvgl.h>
class WeatherTabLvgl
{
private:
    lv_obj_t *container;

    lv_obj_t *date;
    lv_obj_t *min_temp;
    lv_obj_t *max_temp;
    lv_obj_t *weather_desc;
    lv_obj_t *wind_speed;
    lv_obj_t *wind_deg;

public:
    void begin(lv_obj_t *parent);
    lv_obj_t *getContainer();
    void setMinTemp(double temp);
    void setMaxTemp(double temp);
    void setWindSpeed(double speed);
    void setWindDeg(double deg);
    void setDate(const char *date);
    void setWeatherDesc(const char *desc);
};
#endif
