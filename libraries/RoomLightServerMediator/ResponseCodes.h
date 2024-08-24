#ifndef RESPONSE_CODES_H
#define RESPONSE_CODES_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
struct ResponseCodes {
    int okCode = 200;
    int notFoundCode = 404;
    String textPlain = "text/plain";
};
#endif