#include <Servo.h>
#include <RCSwitch.h>
Servo servo;
RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);
  servo.attach(3);
}

void loop() {
  if (mySwitch.available()) {
    Serial.println(mySwitch.getReceivedValue());
    servo.write(mySwitch.getReceivedValue());
    mySwitch.resetAvailable();
  }
}
