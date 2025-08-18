#include <WeatherTabLvgl.h>

void WeatherTabLvgl::begin(lv_obj_t *parent)
{
    this->container = lv_obj_create(parent);
    lv_obj_set_size(this->container, lv_pct(100), LV_SIZE_CONTENT);

    this->date = lv_label_create(this->container);
    lv_obj_set_height(this->date, LV_SIZE_CONTENT);
    lv_label_set_text(this->date, "Date");

    this->min_temp = lv_label_create(this->container);
    lv_obj_set_height(this->min_temp, LV_SIZE_CONTENT);
    lv_label_set_text(this->min_temp, "Min temperature");
    lv_obj_align_to(this->min_temp, this->date, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);

    this->max_temp = lv_label_create(this->container);
    lv_obj_set_height(this->max_temp, LV_SIZE_CONTENT);
    lv_label_set_text(this->max_temp, "Max temperature");
    lv_obj_align_to(this->max_temp, this->min_temp, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);

    this->weather_desc = lv_label_create(this->container);
    lv_obj_set_height(this->weather_desc, LV_SIZE_CONTENT);
    lv_label_set_text(this->weather_desc, "Weather");
    lv_obj_align_to(this->weather_desc, this->max_temp, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);
}

lv_obj_t *WeatherTabLvgl::getContainer()
{
    return this->container;
}

void WeatherTabLvgl::setMinTemp(double value)
{
    char buffer[16];
    dtostrf(value, 6, 2, buffer);
    lv_label_set_text(this->min_temp, buffer);
}

void WeatherTabLvgl::setMaxTemp(double value)
{
    char buffer[16];
    dtostrf(value, 6, 2, buffer);
    lv_label_set_text(this->max_temp, buffer);
}

void WeatherTabLvgl::setDate(const char *date)
{
    lv_label_set_text(this->date, date);
}

void WeatherTabLvgl::setWeatherDesc(const char *desc)
{
    lv_label_set_text(this->weather_desc, desc);
}