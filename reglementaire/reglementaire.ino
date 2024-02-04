// Arduino GPS real time clock with NEO-6M GPS module

#include <TinyGPS++.h>           // Include TinyGPS++ library
#include <SoftwareSerial.h>      // Include software serial library
#include <LiquidCrystal.h>       // Include LCD library

TinyGPSPlus gps;

#define S_RX    8                // Define software serial RX pin
#define S_TX    9               // Define software serial TX pin

SoftwareSerial SoftSerial(S_RX, S_TX);    // Configure SoftSerial library

// LCD module connections (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

byte last_second;
char Time[]  = "TIME:00:00:00";
char Date[]  = "DATE:00/00/2000";

void setup(void) {
  SoftSerial.begin(9600);
  Serial.begin(9600);

  // set up the LCD's number of columns and rows
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print(Time);                           // Display time
  lcd.setCursor(0, 1);
  lcd.print(Date);                           // Display calendar
}

void loop() {

  while (SoftSerial.available() > 0) {

    if (gps.encode(SoftSerial.read())) {

      if (gps.time.isValid()) {
        Time[5]  = gps.time.hour()   / 10 + 48;
        Time[6]  = 2+gps.time.hour()   % 10 + 48;
        Time[8]  = gps.time.minute() / 10 + 48;
        Time[9]  = gps.time.minute() % 10 + 48;
        Time[11] = gps.time.second() / 10 + 48;
        Time[12] = gps.time.second() % 10 + 48;
      }

      if (gps.date.isValid()) {
        Date[5]  = gps.date.day()    / 10 + 48;
        Date[6]  = gps.date.day()    % 10 + 48;
        Date[8]  = gps.date.month()  / 10 + 48;
        Date[9]  = gps.date.month()  % 10 + 48;
        Date[13] =(gps.date.year()   / 10) % 10 + 48;
        Date[14] = gps.date.year()   % 10 + 48;
      }

      if(last_second != gps.time.second()) {
        last_second = gps.time.second();
        lcd.setCursor(0, 0);
        lcd.print(Time);
        Serial.print(Time);                           // Display time
        lcd.setCursor(0, 1);
        lcd.print(Date); 
        Serial.println(Date);                          // Display calendar
      }

    }

  }
  // String latitude = String(gps.location.lat(), 6);
  //   String longitude = String(gps.location.lng(), 6); 

  //  Serial.print ("data longitude : ");
  //  Serial.print (longitude);   
 

  //  Serial.print("data latitude : ");
  //  Serial.println (latitude); 

}