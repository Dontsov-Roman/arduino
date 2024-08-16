#ifndef TRANSFER_STRUCT_H
#define TRANSFER_STRUCT_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

struct TransferStruct {
    long command;
    long value;
};
#endif
