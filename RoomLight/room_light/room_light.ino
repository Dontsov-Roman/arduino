#include <SimpleSensor.h>
#include <SimpleMovementSensor.h>
#include <SimpleDigitalOutput.h>
#include <SoftwareSerial.h>
#include <RoomLightSerial.h>
#include <RoomLightCommands.h>
#include <RoomLightMediator.h>
#include <LocalIpDisplay.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>   

#define SERIAL_BEGIN 9600
#define SOFTWARE_SERIAL_BEGIN 300
#define SOFTWARE_SERIAL_TIMEOUT 1000
#define GLOBAL_DELAY 100

LiquidCrystal_I2C lcd(0x27, 16, 2);
LocalIpDisplay display(&lcd);
SimpleSensor sensorButton(A0);
SimpleMovementSensor movementSensor(A1, 3);
SimpleDigitalOutput led(7);
SoftwareSerial softwareSerial(10, 11); // RX, TX
RoomLightSerial roomSerial(&softwareSerial);
RoomLightMediator mediator(&roomSerial, &sensorButton, &led, &movementSensor, &display);

void setup() {
  Serial.begin(SERIAL_BEGIN);
  
  softwareSerial.begin(SOFTWARE_SERIAL_BEGIN);
  softwareSerial.setTimeout(SOFTWARE_SERIAL_TIMEOUT);
  mediator.begin();
}

void loop() {
  mediator.toggle();
  // delay(GLOBAL_DELAY);
}
