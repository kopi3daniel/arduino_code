// // Made by https://retroetgeek.com

// #include <SimpleDHT.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

// init DHT11
// int pinDHT11 = 2;
// //SimpleDHT11 dht11;

const uint64_t pipeOut = 0xE8E8F0F0E1LL;


struct MyData {
  byte throttle;
  byte yaw;
  byte pitch;
  byte roll;
  byte AUX1;
  byte AUX2;
};

MyData data;

void resetData() 
{
  //This are the start values of each channal
  // Throttle is 0 in order to stop the motors
  //127 is the middle value of the 10ADC.
    
  data.throttle = 0;
  data.yaw = 127;
  data.pitch = 127;
  data.roll = 127;
  data.AUX1 = 0;
  data.AUX2 = 0;
}

int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse)
{
  val = constrain(val, lower, upper);
  if ( val < middle )
    val = map(val, lower, middle, 0, 128);
  else
    val = map(val, middle, upper, 128, 255);
  return ( reverse ? 255 - val : val );
}




void setup() { 
  Serial.begin(115200);

  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);

}

void loop() {

//   byte temperature = 0;
//   byte humidity = 0;
//   int err = SimpleDHTErrSuccess;
//   // if we dont get value from DHT we return to the begining
//   // si nous n'avons pas de valeurs du DHT on reviens au debut avec return
//   if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
//     Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
//     return;
//   }

//   Serial.print((int)temperature); Serial.print(" *C, "); 
//   Serial.print((int)humidity); Serial.println(" H");

// // we send information with 433 and we add 999000 or 888000 for values
// // on envoie l'information ave le 433 et on ajoute 999000 ou 888000 aux valeurs
//     mySwitch.send((999000 + temperature), 24);
//     //delay(1000);
//     mySwitch.send((888000 + humidity), 24);

//   delay(1500);

// data.throttle = mapJoystickValues( analogRead(A0), 13, 524, 1015, true );
//   data.yaw      = mapJoystickValues( analogRead(A1),  1, 505, 1020, true );
//   data.pitch    = mapJoystickValues( analogRead(A2), 12, 544, 1021, true );
//   data.roll     = mapJoystickValues( analogRead(A3), 34, 522, 1020, true );
//   data.AUX1     = digitalRead(7);
//   data.AUX2     = digitalRead(8);


  data.throttle = mapJoystickValues( analogRead(A0), 13, 524, 1015, true );
  data.yaw      = mapJoystickValues( analogRead(A1),  1, 505, 1020, true );
  data.pitch    = mapJoystickValues( analogRead(A2), 12, 544, 1021, true );
  data.roll     = mapJoystickValues( analogRead(A3), 34, 522, 1020, true );
  data.AUX1     = digitalRead(7);
  data.AUX2     = digitalRead(8);

  mySwitch.send(&data, sizeof(MyData));




}
 
