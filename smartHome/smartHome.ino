#include "Relay.h";
#include "RelayComposite.h";

const int BLINK_DELAY = 250;
const int BLINK_PORT = 7;
const int SOUND_PORT = 8;
const int DISABLE_ALL = 0;
const int ENABLE_LIGHT = 1;
const int ENABLE_SOUND = 2;

const int BUFFER_LENGTH = 1;
int sound[2] = {ENABLE_SOUND, SOUND_PORT};
int light[2] = {ENABLE_LIGHT, BLINK_PORT};
int map_ports[2] = {sound, light};

char char_inc[BUFFER_LENGTH] = "0";
int int_inc = 0;

Relay relayLight(BLINK_PORT, ENABLE_LIGHT);
Relay relaySound(SOUND_PORT, ENABLE_SOUND);
const Relay relays[] = {relayLight,relaySound};
const RelayComposite relaysC = RelayComposite(relays);

void enableDisable(int val, int port[])
{
  if ((byte(val) & byte(port[0])) == port[0])
  {
    digitalWrite(port[1], HIGH);
  }
  else
  {
    digitalWrite(port[1], LOW);
  }
}

void enableDisableForAll(int val)
{
  int i;
//  for (i = 0; i < sizeof(map_ports); i = i + 1)
//  {
//    enableDisable(val, map_ports[i]);
//  }
  for (i = 0; i < sizeof(relays); i++)
  {
    relays[i].toggle(val);
  }
}
void setup()
{
  Serial.begin(9600);
  pinMode(BLINK_PORT, OUTPUT);
  pinMode(SOUND_PORT, OUTPUT);
}

void loop()
{
  if (Serial.available() > 0)
  {
    Serial.readBytes(char_inc, BUFFER_LENGTH);
    Serial.println(char_inc);
    int_inc = String(char_inc).toInt();
    Serial.println(int_inc);
    relaysC.toggle(int_inc);
//    enableDisableForAll(int_inc);
  }
}
