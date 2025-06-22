#include <LvglBaseObject.h>

LvglBaseObject::LvglBaseObject(lv_obj_t *parent)
{
    this->parent = parent;
    this->obj = lv_obj_create(this->parent);
}

void LvglBaseObject::setBackgroundColor(lv_color_t color)
{
    lv_obj_set_style_bg_color(this->obj, color, 0);
}

void LvglBaseObject::setSize(lv_coord_t width, lv_coord_t height)
{
    lv_obj_set_size(this->obj, width, height);
}

void LvglBaseObject::setAlign(lv_align_t align, lv_coord_t x, lv_coord_t y)
{
    lv_obj_align(this->obj, align, x, y);
}

void LvglBaseObject::setFlexFlow(lv_flex_flow_t flow)
{
    lv_obj_set_flex_flow(this->obj, flow);
}

void LvglBaseObject::setFlexAlign(lv_flex_align_t main_place, lv_flex_align_t cross_place, lv_flex_align_t track_place)
{
    lv_obj_set_flex_align(this->obj, main_place, cross_place, track_place);
}
void LvglBaseObject::setText(const char *text)
{
    lv_label_set_text(this->obj, text);
}

void LvglBaseObject::setStyle(lv_style_t *style)
{
    lv_obj_add_style(this->obj, style, 0);
}

lv_obj_t *LvglBaseObject::getNativeObject()
{
    return this->obj;
}

void LvglBaseObject::setNativeObject(lv_obj_t *obj)
{
    this->obj = obj;
}