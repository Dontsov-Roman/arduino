#ifndef ROOM_LIGHT_COMMANDS_H
#define ROOM_LIGHT_COMMANDS_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// enum RoomLightCommands {
//     Nothing = '0',
//     SwitchOff = '1',
//     SwitchOn = '2',
//     MovementMode = '3',
//     SetLocalIp = '4',
// };
const int NothingCommand = 0;
const int SwitchOffCommand = 1;
const int SwitchOnCommand = 2;
const int MovementModeCommand = 3;
const int SetLocalIpCommand = 4;
#endif