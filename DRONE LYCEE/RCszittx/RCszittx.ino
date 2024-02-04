// Made by https://retroetgeek.com

#include <SimpleDHT.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

// init DHT11
int pinDHT11 = 2;
SimpleDHT11 dht11;

void setup() { 
  Serial.begin(115200);

  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);

}

void loop() {

  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  // if we dont get value from DHT we return to the begining
  // si nous n'avons pas de valeurs du DHT on reviens au debut avec return
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }

  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");

// we send information with 433 and we add 999000 or 888000 for values
// on envoie l'information ave le 433 et on ajoute 999000 ou 888000 aux valeurs
    mySwitch.send((999000 + temperature), 24);
    //delay(1000);
    mySwitch.send((888000 + humidity), 24);

  delay(1500);

}