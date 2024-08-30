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
    this->currentMilSec = millis();
    if (this->currentMilSec - this->lastUpdateMillis > this->timeout) {
        this->lastUpdateMillis = this->currentMilSec;
        return true;
    }
    return false;
}