
const auto BLINK_DELAY = 250;
const auto BLINK_PORT = 7;
const auto SOUND_PORT = 8;
const auto DISABLE_ALL = 0;
const int ENABLE_LIGHT = 1;
const int ENABLE_SOUND = 2;

const int BUFFER_LENGTH = 2;
int sound[2] = {ENABLE_SOUND,SOUND_PORT};
int light[2] = {ENABLE_LIGHT,BLINK_PORT};
int map_ports[2] = {sound,light};

char char_inc[BUFFER_LENGTH] = "0";
int int_inc = 0;

void enableDisable(int val, int port[]) {
  if((byte(val) & byte(port[0])) == port[0]) {
    digitalWrite(port[1], HIGH);
  }
  else {
    digitalWrite(port[1], LOW);
  }
}

void enableDisableForAll(int val) {
  int i;
  for (i = 0; i < sizeof(map_ports); i = i + 1) {
    enableDisable(val, map_ports[i]);
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BLINK_PORT, OUTPUT);
  pinMode(SOUND_PORT, OUTPUT);
}

void loop() {
  if(Serial.available() > 0) {
    Serial.readBytes(char_inc,BUFFER_LENGTH);
    Serial.println(char_inc);
    int_inc = String(char_inc).toInt();
    Serial.println(int_inc);
    enableDisableForAll(int_inc);
  }
}
