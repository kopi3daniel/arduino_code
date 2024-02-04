// // Made by https://retroetgeek.com

#include <RCSwitch.h>
// call 433 library
RCSwitch mySwitch = RCSwitch();

// String temporaryValue ;
// int temperature = 0 ;
// int humidite = 0 ;
// long oldDataTime;

////////////////////// PPM CONFIGURATION//////////////////////////
#define channel_number 6  //set the number of channels
#define sigPin 2  //set PPM signal output pin on the arduino
#define PPM_FrLen 27000  //set the PPM frame length in microseconds (1ms = 1000µs)
#define PPM_PulseLen 400  //set the pulse length
//////////////////////////////////////////////////////////////////

int ppm[channel_number];

const uint64_t pipeIn =  0xE8E8F0F0E1LL;


// The sizeof this struct should not exceed 32 bytes
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
  // 'safe' values to use when no radio input is detected
  data.throttle = 0;
  data.yaw = 127;
  data.pitch = 127;
  data.roll = 127;
  data.AUX1 = 0;
  data.AUX2= 0;
  
  setPPMValuesFromData();
}

void setPPMValuesFromData()
{
  ppm[0] = map(data.throttle, 0, 255, 1000, 2000);
  ppm[1] = map(data.yaw,      0, 255, 1000, 2000);
  ppm[2] = map(data.pitch,    0, 255, 1000, 2000);
  ppm[3] = map(data.roll,     0, 255, 1000, 2000);
  ppm[4] = map(data.AUX1,     0, 1, 1000, 2000);
  ppm[5] = map(data.AUX2,     0, 1, 1000, 2000);  
  }



/**************************************************/

void setupPPM() {
  pinMode(sigPin, OUTPUT);
  digitalWrite(sigPin, 0);  //set the PPM signal pin to the default state (off)

  cli();
  TCCR1A = 0; // set entire TCCR1 register to 0
  TCCR1B = 0;

  OCR1A = 100;  // compare match register (not very important, sets the timeout for the first interrupt)
  TCCR1B |= (1 << WGM12);  // turn on CTC mode
  TCCR1B |= (1 << CS11);  // 8 prescaler: 0,5 microseconds at 16mhz
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  sei();
}
unsigned long lastRecvTime = 0;

void recvData()
{  
  while ( mySwitch.available() ) {        
   // mySwitch.getReceivedD(&data, sizeof(MyData));
      //radio.read(&data, sizeof(MyData));
      mySwitch.getReceivedValue();
      Serial.println(mySwitch.getReceivedValue());
    lastRecvTime = millis();
  }
}


void setup() {

  resetData();
  setupPPM();
  Serial.begin(115200);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
}

#define clockMultiplier 2 

//#error Delete this line befor you cahnge the value (clockMultiplier) below
// set this to 2 if you are using a 16MHz arduino, leave as 1 for an 8MHz arduino

ISR(TIMER1_COMPA_vect){
  static boolean state = true;

  TCNT1 = 0;

  if ( state ) {
    //end pulse
    PORTD = PORTD & ~B00000100; // turn pin 2 off. Could also use: digitalWrite(sigPin,0)
    OCR1A = PPM_PulseLen * clockMultiplier;
    state = false;
  }
  else {
    //start pulse
    static byte cur_chan_numb;
    static unsigned int calc_rest;

    PORTD = PORTD | B00000100; // turn pin 2 on. Could also use: digitalWrite(sigPin,1)
    state = true;

    if(cur_chan_numb >= channel_number) {
      cur_chan_numb = 0;
      calc_rest += PPM_PulseLen;
      OCR1A = (PPM_FrLen - calc_rest) * clockMultiplier;
      calc_rest = 0;
    }
    else {
      OCR1A = (ppm[cur_chan_numb] - PPM_PulseLen) * clockMultiplier;
      calc_rest += ppm[cur_chan_numb];
      cur_chan_numb++;
    }     
  }
}


void loop() {

  recvData();

  unsigned long now = millis();
  if ( now - lastRecvTime > 1000 ) {
    // signal lost?
    resetData();
  }
  
  setPPMValuesFromData();


//   if (mySwitch.available()) {

//     int value = mySwitch.getReceivedValue();

//     if (value == 0) {
//       Serial.print("Unknown encoding");
//     } else {
// /*      Serial.print("Received ");
//       Serial.print( mySwitch.getReceivedValue() );
//       Serial.print(" / ");
//       Serial.print( mySwitch.getReceivedBitlength() );
//       Serial.print("bit ");
//       Serial.print("Protocol: ");
//       Serial.println( mySwitch.getReceivedProtocol() );*/
//     }

//     // get data and split values
//     // on recupere la data et on separe les valeurs
//     temporaryValue = String(mySwitch.getReceivedValue());
//     if(temporaryValue.substring(0,3) == "999"){
//       temperature = temporaryValue.substring(3).toInt() ;
//     }  
//     if(temporaryValue.substring(0,3) == "888"){
//       humidite = temporaryValue.substring(3).toInt() ;
//     }

//     // reset 433
//     mySwitch.resetAvailable();

//     oldDataTime = millis();

//   }
//   // control if we lost information , 10 second 
//   // On controle si on a perdu le signal depuis plus de 10secondes
//   if(millis() > (oldDataTime + 10000) ){
//     temperature = 999 ;
//     humidite = 999 ;
//   }

//   // print value
//   // on affiche les valeurs
//       Serial.print("Temperature: ");
//       Serial.println(temperature);
//       //Serial.print("Humidite: ");
//       //Serial.println(humidite);

//   //delay(2000);
}

