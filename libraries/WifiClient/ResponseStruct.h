#ifndef RESPONSE_STRUCT_H
#define RESPONSE_STRUCT_H

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

struct ResponseStruct {
    int code;
    String response;
};
#endif
