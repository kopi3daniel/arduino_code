#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableTransmit(10);
}

void loop() {
  int value = analogRead(A1);
  value = map(value, 0, 1024, 0, 180);
  mySwitch.send(value, 30);
}
