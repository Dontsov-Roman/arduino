#include <GpsSaver.h>

GpsSaver::GpsSaver() {
}
void GpsSaver::addData(String str) {
    if (this->data.isEmpty()) {
        this->data = cppQueue(sizeof(str));
    }
    if (this->data.isFull()) {
        this->data.pop(&this->last);
    }
    this->data.push(&str);
}