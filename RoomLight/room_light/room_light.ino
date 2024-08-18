#include <SimpleSensor.h>
#include <SimpleMovementSensor.h>
#include <SimpleDigitalOutput.h>
#include <SoftwareSerial.h>
#include <RoomLightSerial.h>

#define SERIAL_BEGIN 9600
#define GLOBAL_DELAY 200

SimpleSensor sensorButton(A0);
SimpleMovementSensor moveSensor(A1, 3);
SimpleDigitalOutput led(7);
SoftwareSerial mySerial(10, 11); // RX, TX
RoomLightSerial roomSerial(&mySerial);

void setup() {
  Serial.begin(SERIAL_BEGIN);
  mySerial.begin(SERIAL_BEGIN);
  // led.begin();
  // moveSensor.calibrate();
}

void loop() {
  
  // sensorButton.read();
  // moveSensor.read();
  // roomSerial.write(15, 150);
  roomSerial.read();
  // Serial.println(transferStruct.code);
  // Serial.println("Move:");
  // moveSensor.statusToSerial();
  // Serial.println("Button:");
  // sensorButton.statusToSerial();
  if (!sensorButton.isOn() || moveSensor.isOn()) {
    led.switchOn();
  } else {
    led.switchOff();
  }
  delay(GLOBAL_DELAY);
}
