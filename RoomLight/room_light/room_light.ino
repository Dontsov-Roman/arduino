#include <SimpleSensor.h>
#include <SimpleMovementSensor.h>
#include <SimpleDigitalOutput.h>
#include <SoftwareSerial.h>
#include <RoomLightSerial.h>
#include <TransferStruct.h>

SimpleSensor sensorButton(A0);
SimpleMovementSensor moveSensor(A1, 3);
SimpleDigitalOutput led(7);
SoftwareSerial mySerial(10, 11); // RX, TX
TransferStruct readStruct;
TransferStruct writeStruct;
RoomLightSerial roomSerial(&mySerial, &readStruct, &writeStruct);

void setup() {
  Serial.begin(9600);
  led.begin();
  led.switchOff();
  Serial.println(HIGH);
  Serial.println(LOW);
  moveSensor.calibrate();
}

void loop() {
  sensorButton.read();
  moveSensor.read();
  // Serial.println("Move:");
  // moveSensor.statusToSerial();
  // Serial.println("Button:");
  // sensorButton.statusToSerial();
  if (!sensorButton.isOn() || moveSensor.isOn()) {
    led.switchOn();
  } else {
    led.switchOff();
  }
  delay(300);
}
