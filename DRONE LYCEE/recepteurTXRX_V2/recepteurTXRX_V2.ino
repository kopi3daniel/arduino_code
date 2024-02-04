/* Receiver code for the Arduino Radio control with PWM output
 *  
 *  THIS ONLY WORKS WITH ATMEGA328p registers!!!!
 *  It gives a shifty PWM due to radio receive without interuption. Still working on it
 *  
 *  Install the NRF24 library to your IDE
 * Upload this code to the Arduino UNO
 * Connect a NRF24 module to it:
 
    Module // Arduino UNO
    
    GND    ->   GND
    Vcc    ->   3.3V
    CE     ->   D9
    CSN    ->   D10
    CLK    ->   D13
    MOSI   ->   D11
    MISO   ->   D12

This code receive 6 channels and create a PWM output for each one on D2, D3, D4, D5, D6 and D7
Please, like share and subscribe : https://www.youtube.com/c/ELECTRONOOBS
*/

//Define widths
int pwm_width_2 = 0;
int pwm_width_3 = 0;
int pwm_width_4 = 0;
int pwm_width_5 = 0;
int pwm_width_6 = 0;
int pwm_width_7 = 0;


float frequency = 62.5;                     // PWM frequency in hertz
float PWM_period = ((1/frequency)*1000000);   //period in us 
unsigned long previousMillis = 0;                            //Set initial timer value used for the PWM signal

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipeIn = 0xE8E8F0F0E1LL;     //Remember that this code is the same as in the transmitter

RF24 radio(9, 10); 

                    //We could use up to 32 channels
struct MyData {
byte throttle;      //We define each byte of data input, in this case just 6 channels
byte yaw;
byte pitch;
byte roll;
byte AUX1;
byte AUX2;
};

MyData data;

void resetData()
{
//We define the inicial value of each data input
//3 potenciometers will be in the middle position so 127 is the middle from 254
data.throttle = 0;
data.yaw = 127;
data.pitch = 127;
data.roll = 127;
data.AUX1 = 0;
data.AUX2 = 0;

}

/**************************************************/

void setup()
{
  //Set the timer

  cli();
  TCCR1A = 0; // set entire TCCR1 register to 0
  TCCR1B = 0;

  OCR1A = 100;  // compare match register (not very important, sets the timeout for the first interrupt)
  TCCR1B |= (1 << WGM12);  // turn on CTC mode
  TCCR1B |= (1 << CS11);  // 8 prescaler: 0,5 microseconds at 16mhz
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  sei();



  
// Register valeus: D7:D6:D5:D4:D3:D2:D1:D0
DDRD |= B11111100;  // Sets D2, D3, D4, D5, D6 and D7 as input 

resetData();
radio.begin();
radio.setAutoAck(false);
radio.setDataRate(RF24_250KBPS);

radio.openReadingPipe(1,pipeIn);
//we start the radio comunication
radio.startListening();

}

/**************************************************/

unsigned long lastRecvTime = 0;

void recvData()
{
while ( radio.available() ) {
radio.read(&data, sizeof(MyData));
lastRecvTime = millis(); //here we receive the data
}
}

/**************************************************/

void loop()
{
recvData();
unsigned long now = millis();
//Here we check if we've lost signal, if we did we reset the values 
if ( now - lastRecvTime > 1000 ) {
// Signal lost?
resetData();
}

pwm_width_2 = map(data.throttle, 0, 255, 1000, 2000);     //PWM value on digital pin D3
pwm_width_3 = map(data.yaw,      0, 255, 1000, 2000);     //PWM value on digital pin D4
pwm_width_4 = map(data.pitch,    0, 255, 1000, 2000);     //PWM value on digital pin D5
pwm_width_5 = map(data.roll,     0, 255, 1000, 2000);     //PWM value on digital pin D6
pwm_width_6 = map(data.AUX1,     0, 255, 1000, 2000);     //PWM value on digital pin D6
pwm_width_7 = map(data.AUX2,     0, 255, 1000, 2000);     //PWM value on digital pin D6
}//Loop end
/**************************************************/






//Timer interrupt
ISR(TIMER1_COMPA_vect){
  unsigned long currentMillis = micros();
//////////////////////PWM signal/////////////////////////
if(currentMillis - previousMillis < PWM_period) //we need a 16ms period of the signal.
 {
    
  ////Pin D2-Throttle////
  if(currentMillis - previousMillis < pwm_width_2)
  {
    PORTD |= B00000100;    // Sets to HIGH D2.     
  }

  if(currentMillis - previousMillis > pwm_width_2)
  {
    PORTD &= B11111011;    // Sets to LOW D2.
  }
  
  ////Pin D3-Yaw////
  if(currentMillis - previousMillis < pwm_width_3)
  {
    PORTD |= B00001000;    // Sets to HIGH D3.     
  }

  if(currentMillis - previousMillis > pwm_width_3)
  {
    PORTD &= B11110111;    // Sets to LOW D3.
  }  
  
  ////Pin D4-Pitch////
  if(currentMillis - previousMillis < pwm_width_4)
  {
    PORTD |= B00010000;    // Sets to HIGH D4.     
  }

  if(currentMillis - previousMillis > pwm_width_4)
  {
    PORTD &= B11101111;    // Sets to LOW D4.
  }
  
  ////Pin D5-Roll////
  if(currentMillis - previousMillis < pwm_width_5)
  {
    PORTD |= B00100000;    // Sets to HIGH D5.     
  }

  if(currentMillis - previousMillis > pwm_width_5)
  {
    PORTD &= B11011111;    // Sets to LOW D5.
  }
  
  ////Pin D6-Aux1////
  if(currentMillis - previousMillis < pwm_width_6)
  {
    PORTD |= B01000000;    // Sets to HIGH D6.     
  }

  if(currentMillis - previousMillis > pwm_width_6)
  {
    PORTD &= B10111111;    // Sets to LOW D6.
  } 

 ////Pin D7-Aux2////
  if(currentMillis - previousMillis < pwm_width_7)
  {
    PORTD |= B10000000;    // Sets to HIGH D7.     
  }

  if(currentMillis - previousMillis > pwm_width_7)
  {
    PORTD &= B01111111;    // Sets to LOW D7.
  } 
 } //ends the if (currentMillis - previousMillis < PWM_period)


 if(currentMillis - previousMillis > PWM_period) //We reach 16ms and reset the timer
  {
   previousMillis += PWM_period;
  }
}

 
