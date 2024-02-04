#include <VirtualWire.h>

char *controller;


void setup() {
 pinMode(8,INPUT_PULLUP);
 Serial.begin(9600);
 vw_set_ptt_inverted(true);
 vw_set_tx_pin(12);
 vw_setup(4000);
 pinMode(13, OUTPUT);

}

void loop() {

  if(digitalRead(8)==LOW){
    controller="1";
    vw_send((uint8_t *)controller,strlen(controller));
    vw_wait_tx();
    digitalWrite(13, HIGH);
    Serial.println("donner");
  }

  else{
    controller="0";
    vw_send((uint8_t *)controller,strlen(controller));
    vw_wait_tx();
    digitalWrite(13, LOW);

    Serial.println("donner 0");

  }
  
}
