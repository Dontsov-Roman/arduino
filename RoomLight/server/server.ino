#include <SoftwareSerial.h>
#include <RoomLightSerial.h>
#include <RoomLightCommands.h>

#define SERIAL_BEGIN 9600
#define GLOBAL_DELAY 200

SoftwareSerial mySerial(D5, D6); // RX, TX
TransferStruct transferStruct;
RoomLightSerial roomSerial(&mySerial);

void setup() {
  Serial.begin(SERIAL_BEGIN);
  mySerial.begin(SERIAL_BEGIN);
}

void loop() {
  // roomSerial.read();
  roomSerial.write(SwitchOn, 150);
  // Serial.println(transferStruct.code);
  delay(GLOBAL_DELAY);
}
