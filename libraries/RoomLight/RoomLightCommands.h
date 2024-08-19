#ifndef ROOM_LIGHT_COMMANDS_H
#define ROOM_LIGHT_COMMANDS_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

enum RoomLightCommands {
    SwitchOff,
    SwitchOn,
    MovementMode,
    SetLocalIp,
};
#endif