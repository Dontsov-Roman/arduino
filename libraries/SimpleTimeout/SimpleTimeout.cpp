#include <SimpleTimeout.h>

SimpleTimeout::SimpleTimeout() {
    this->timeout = SIMPLE_DEFAULT_TIMEOUT;
    this->lastUpdateMillis = 0;
}

SimpleTimeout::SimpleTimeout(int timeout) {
    this->timeout = timeout;
    this->lastUpdateMillis = 0;
}

bool SimpleTimeout::checkTimeout() {
    int mil_sec = millis();
    if (mil_sec - this->lastUpdateMillis > this->timeout) {
        this->lastUpdateMillis = mil_sec;
        return true;
    }
    return false;
}