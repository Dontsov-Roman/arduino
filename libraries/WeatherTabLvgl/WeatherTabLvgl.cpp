#include <WeatherTabLvgl.h>

void WeatherTabLvgl::begin(lv_obj_t *parent)
{
    this->container = lv_obj_create(parent);
    lv_obj_set_size(this->container, lv_pct(30), LV_SIZE_CONTENT);

    this->date = lv_label_create(this->container);
    lv_obj_set_height(this->date, LV_SIZE_CONTENT);
    lv_label_set_text(this->date, "Date");

    this->min_temp = lv_label_create(this->container);
    lv_obj_t *min_temp_label = lv_label_create(this->container);
    lv_obj_set_height(this->min_temp, LV_SIZE_CONTENT);
    lv_obj_set_height(min_temp_label, LV_SIZE_CONTENT);
    lv_label_set_recolor(min_temp_label, true);
    lv_label_set_text(min_temp_label, "#0000ff Min temperature:");
    lv_obj_align_to(min_temp_label, this->date, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);
    lv_obj_align_to(this->min_temp, min_temp_label, LV_ALIGN_OUT_RIGHT_MID, 10, 0);

    this->max_temp = lv_label_create(this->container);
    lv_obj_t *max_temp_label = lv_label_create(this->container);
    lv_obj_set_height(this->max_temp, LV_SIZE_CONTENT);
    lv_obj_set_height(max_temp_label, LV_SIZE_CONTENT);
    lv_label_set_recolor(max_temp_label, true);
    lv_label_set_text(max_temp_label, "#0000ff Max temperature:");
    lv_obj_align_to(max_temp_label, min_temp_label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);
    lv_obj_align_to(this->max_temp, max_temp_label, LV_ALIGN_OUT_RIGHT_MID, 10, 0);

    this->weather_desc = lv_label_create(this->container);
    lv_obj_set_height(this->weather_desc, LV_SIZE_CONTENT);
    lv_label_set_text(this->weather_desc, "Weather");
    lv_obj_align_to(this->weather_desc, max_temp_label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);

    lv_obj_t *wind_label = lv_label_create(this->container);
    lv_obj_t *wind_units = lv_label_create(this->container);
    this->wind_speed = lv_label_create(this->container);
    this->wind_deg = lv_label_create(this->container);
    lv_obj_set_height(this->wind_speed, LV_SIZE_CONTENT);
    lv_obj_set_height(wind_units, LV_SIZE_CONTENT);
    lv_obj_set_height(this->wind_deg, LV_SIZE_CONTENT);
    lv_obj_set_height(wind_label, LV_SIZE_CONTENT);
    lv_label_set_recolor(wind_label, true);
    lv_label_set_text(wind_label, "#0000ff Wind:");

    lv_label_set_recolor(wind_units, true);
    lv_label_set_text(wind_units, "#0000ff m/sec");

    lv_obj_align_to(wind_label, this->weather_desc, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);
    lv_obj_align_to(this->wind_speed, wind_label, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_align_to(wind_units, this->wind_speed, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_align_to(this->wind_deg, wind_units, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
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

void WeatherTabLvgl::setWindSpeed(double value)
{
    char buffer[16];
    dtostrf(value, 6, 2, buffer);
    lv_label_set_text(this->wind_speed, buffer);
}

void WeatherTabLvgl::setWindDeg(double value)
{
    char buffer[16];
    dtostrf(value, 6, 2, buffer);
    lv_label_set_text(this->wind_deg, buffer);
}

void WeatherTabLvgl::setDate(const char *value)
{
    lv_label_set_text(this->date, value);
}

void WeatherTabLvgl::setWeatherDesc(const char *value)
{
    lv_label_set_text(this->weather_desc, value);
}