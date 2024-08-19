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
#define GLOBAL_DELAY 1200

LiquidCrystal_I2C lcd(0x27, 16, 2);
LocalIpDisplay display(&lcd);
SimpleSensor sensorButton(A0);
SimpleMovementSensor movementSensor(A1, 3);
SimpleDigitalOutput led(7);
SoftwareSerial softwareSerial(10, 11); // RX, TX
RoomLightSerial roomSerial(&softwareSerial);
RoomLightMediator mediator(&roomSerial, &sensorButton, &led, &movementSensor, &display);

// TransferStruct ts;
// char ipAddr[] = "192.168.0.113";

void setup() {
  Serial.begin(SERIAL_BEGIN);
  
  // ts.command = SetLocalIp;
  // ts.address = "192.168.0.113";
  softwareSerial.begin(SERIAL_BEGIN);
  mediator.begin();
  // delay(3000);
}

void loop() {
  mediator.toggle();
  // Serial.println("TS:");
  // Serial.println(sizeof(ts));
  // Serial.println("Address:");
  // Serial.println(sizeof(ts.address));
  // Serial.println("Char:");
  // Serial.println(sizeof(ipAddr));
  delay(1000);
}
