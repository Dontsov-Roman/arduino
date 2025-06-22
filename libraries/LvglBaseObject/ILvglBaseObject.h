#ifndef I_LVGL_OBJECT_H
#define I_LVGL_OBJECT_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class ILvglBaseObject
{
public:
    virtual void setBackgroundColor(lv_color_t color);
    virtual void setSize(lv_coord_t width, lv_coord_t height);
    virtual void setAlign(lv_align_t align, lv_coord_t x, lv_coord_t y);
    virtual void setFlexFlow(lv_flex_flow_t flow);
    virtual void setFlexAlign(lv_flex_align_t main_place, lv_flex_align_t cross_place, lv_flex_align_t track_place);
    virtual void setText(const char *text);
    virtual void setStyle(lv_style_t *style);
};
#endif
