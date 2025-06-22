#ifndef LVGL_OBJECT_H
#define LVGL_OBJECT_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <lvgl.h>
#include <ILvglBaseObject.h>
class LvglBaseObject : public ILvglBaseObject
{
public:
    LvglBaseObject(lv_obj_t *parent);
    void setBackgroundColor(lv_color_t color);
    void setSize(lv_coord_t width, lv_coord_t height);
    void setAlign(lv_align_t align, lv_coord_t x, lv_coord_t y);
    void setFlexFlow(lv_flex_flow_t flow);
    void setFlexAlign(lv_flex_align_t main_place, lv_flex_align_t cross_place, lv_flex_align_t track_place);
    void setText(const char *text);
    void setStyle(lv_style_t *style);
    lv_obj_t *getNativeObject();
    void setNativeObject(lv_obj_t *obj);

protected:
    lv_obj_t *parent;
    lv_obj_t *obj;
};
#endif
