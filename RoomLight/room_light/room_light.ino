#include <SimpleSensor.h>
#include <SimpleMovementSensor.h>
#include <SimpleDigitalOutput.h>
#include <SoftwareSerial.h>
#include <RoomLightSerial.h>
#include <RoomLightCommands.h>
#include <RoomLightMediator.h>

#define SERIAL_BEGIN 9600
#define GLOBAL_DELAY 200

SimpleSensor sensorButton(A0);
SimpleMovementSensor movementSensor(A1, 3);
SimpleDigitalOutput led(7);
SoftwareSerial softwareSerial(10, 11); // RX, TX
RoomLightSerial roomSerial(&softwareSerial);
RoomLightMediator mediator(&roomSerial, &sensorButton, &led, &movementSensor);

void setup() {
  Serial.begin(SERIAL_BEGIN);
  softwareSerial.begin(SERIAL_BEGIN);
  mediator.begin();
}

void loop() {
  mediator.toggle();
  delay(GLOBAL_DELAY);
}
