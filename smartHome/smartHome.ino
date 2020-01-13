#include "Relay.h";

const int BLINK_DELAY = 250;
const int BLINK_PORT = 7;
const int SOUND_PORT = 8;
const int DISABLE_ALL = 0;
const int ENABLE_LIGHT = 1;
const int ENABLE_SOUND = 2;

const int BUFFER_LENGTH = 1;

char char_inc[BUFFER_LENGTH] = "0";
int int_inc = 0;

Relay relayLight(BLINK_PORT, ENABLE_LIGHT);
Relay relaySound(SOUND_PORT, ENABLE_SOUND);
const Relay relays[] = {relayLight,relaySound};
//SimpleList<Relay> *mySimpleList = new SimpleList<Relay>();

void enableDisableForAll(int val)
{
  int i;
  for (i = 0; i < sizeof(relays); i++)
  {
    relays[i].toggle(val);
  }
}
void setup()
{
  Serial.begin(9600);
//  relayList.add(relayLight);
  pinMode(BLINK_PORT, OUTPUT);
  pinMode(SOUND_PORT, OUTPUT);
}

void loop()
{
  if (Serial.available() > 0)
  {
    Serial.readBytes(char_inc, BUFFER_LENGTH);
    int_inc = String(char_inc).toInt();
    enableDisableForAll(int_inc);
  }
}
