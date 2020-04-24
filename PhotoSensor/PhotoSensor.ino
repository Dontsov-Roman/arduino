#include "PhotoSensor.h"
#include "Relay.h"
#include "MoveSensor.h"
#include "BleSensor.h"
#include "MoveBleMediator.h"

const int PHOTO_PIN = A0;
const int LIGHT_PIN = D6;
const int MOVE_PIN = D1;

const int MOVE_BIT = 1;
const int THRESHOLD_PHOTO = 10;

PhotoSensor PS(PHOTO_PIN, THRESHOLD_PHOTO);

Relay MoveRel(MOVE_PIN, MOVE_BIT);

Relay LightRel(LIGHT_PIN, MOVE_BIT);

MoveSensor MS(&MoveRel,&LightRel, &PS, PHOTORESISTOR);

BleSensor BS;

MoveBleMediator MBM(&MS, &BS);

void setup() {
  pinMode(PHOTO_PIN, INPUT);
  pinMode(MOVE_PIN, INPUT);
  pinMode(LIGHT_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  MBM.read();
  delay(1500);
}
