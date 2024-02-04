#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL2Ujw1HkGS" // replace this with template id
#define BLYNK_TEMPLATE_NAME "AFRITECH" // replace this with your device name
#define BLYNK_AUTH_TOKEN   "QUxTc1wO7HNYqHYEb4dvTp6eZPzza2gE"

#include <ESP8266WiFi.h> // importing all the required libraries
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>


 #include <SoftwareSerial.h>  
 #include <DHT.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define echo D6

#define trigger D5

 String informationcapteur; 


LiquidCrystal_I2C  lcd (0x27 , 16 , 2);
 DHT dht(D7 , DHT11);
 
  SoftwareSerial receptiondatacapteur(D2,D1);

    const long distancemax = 190;

   long quantitee_pluie; 


float temperature ; // parameters
float humiditee;
float pressure = 1;
float mbar = 10;
float uv = 1;
float visible = 4;
float ir = 1;

 boolean etatprovision;
  



char auth[] = "QUxTc1wO7HNYqHYEb4dvTp6eZPzza2gE"; // replace this with your auth token
char ssid[] = "ing kopi3"; // replace this with your wifi name (SSID)
char pass[] = "1234567890"; // replace this with your wifi password


BlynkTimer timer;


  String datadirectionvent;
   String datavitessevent; 
    String dataintensiteesoleil; 
     String datapluie;



     
   float datadirectionventfloat;
   float datavitesseventfloat; 
    float dataintensiteesoleilfloat; 
     float datapluiefloat;

void sendSensor() // function to read sensor values and send them to Blynk
{

    etatprovision = digitalRead(D8);
    
//  humiditee = dht.readHumidity();
//   temperature = dht.readTemperature();
  humiditee = 34.80;
  temperature = 12.00;


   lcd.setCursor(0,0);
    lcd.print("t:");
     lcd.setCursor(2,0);
    lcd.print(temperature);

     lcd.setCursor(8,0);
    lcd.print("h:");
     lcd.setCursor(10,0);
    lcd.print(humiditee);


       float   quantiteepluie  ;
    digitalWrite(trigger , LOW);
     delayMicroseconds(2); 
      digitalWrite(trigger , HIGH);
     delayMicroseconds(10);
       digitalWrite(trigger , LOW); 

      quantiteepluie = distancemax - (pulseIn(echo , HIGH)/58.0)*10; 
       quantiteepluie = quantiteepluie - 4.00;
       if(quantiteepluie < 0)  { 
          quantiteepluie = 0; 
       }

 lcd.setCursor(0,1);
    lcd.print("P:");
     lcd.setCursor(2,1);
    lcd.print(quantiteepluie);
    lcd.print("  ");

     if (receptiondatacapteur.available()) { 
      informationcapteur = receptiondatacapteur.readString(); 
      Serial.println(informationcapteur); 
       Serial.println("info recu");

        datadirectionvent = informationcapteur.substring(0,2); 
         datapluie = informationcapteur.substring(4,10);
           dataintensiteesoleil = informationcapteur.substring(11,17);
            datavitessevent = informationcapteur.substring(19 , 24);

           Serial.println(datadirectionvent);
            Serial.println(datapluie);
             Serial.println(dataintensiteesoleil);
              Serial.println(datavitessevent);
              
                Serial.println();
                
 //datadirectionventfloat = datadirectionvent.toFloat();
   datavitesseventfloat = datavitessevent.toFloat(); 
    dataintensiteesoleilfloat = dataintensiteesoleil.toFloat() * 3; 
     datapluiefloat = 100-(datapluie.toFloat() * 100/1023);

     Serial.print("valeur en float :");
       Serial.println(datapluiefloat);
       Serial.println();
       Serial.println();

             } 


     
    
//  if (isnan(humidity) || isnan(temperature)) 
//  {
//    Serial.println("Failed to read from DHT sensor!");
//    return;
//  }
//
//  pressure = myBarometer.bmp085GetPressure(myBarometer.bmp085ReadUP()); // read pressure value in pascals
//  mbar = pressure / 100; // convert millibar to pascals
//  visible = SI1145.ReadVisible(); // visible radiation
//  ir = SI1145.ReadIR(); // IR radiation
//  uv = SI1145.ReadUV(); // UV index

 lcd.setCursor(8,1);
  lcd.print("DV:");
   lcd.setCursor(11,1);
    lcd.print(datadirectionvent);
     lcd.print(" ");

  Blynk.virtualWrite(V0, temperature); // send all the values to their respective virtual pins
  Blynk.virtualWrite(V1, humiditee);
  Blynk.virtualWrite(V2, dataintensiteesoleilfloat);
  Blynk.virtualWrite(V3, quantiteepluie);
  Blynk.virtualWrite(V4, datapluiefloat);  
  Blynk.virtualWrite(V5, datavitesseventfloat);

  
   if(datadirectionvent == "NN") {
     Blynk.virtualWrite(V6, "VERS NORD");
   }

   if(datadirectionvent == "SS") {
     Blynk.virtualWrite(V6, "VERS SUD");
   }

   if(datadirectionvent == "OO") {
     Blynk.virtualWrite(V6, "VERS OUEST");
   }

   if(datadirectionvent == "EE") {
     Blynk.virtualWrite(V6, "VERS EST");
   }

    if(datadirectionvent == "NO") {
     Blynk.virtualWrite(V6, "VERS NORD OUEST");
   }

    if(datadirectionvent == "NE") {
     Blynk.virtualWrite(V6, "VERS NORD EST");
   }

     if(datadirectionvent == "SO") {
     Blynk.virtualWrite(V6, "VERS SUD OUEST");
   }

    if(datadirectionvent == "SE") {
     Blynk.virtualWrite(V6, "VERS SUD EST");
   }

     if(etatprovision == true && datadirectionvent == "OO"){ 
        Blynk.virtualWrite(V7, "> 80% "); 
     } 

      if(etatprovision == true && (datadirectionvent == "SO" ||  datadirectionvent == "SE")){
        Blynk.virtualWrite(V7, "> 50%");
      }

       if(etatprovision == false) { 
            Blynk.virtualWrite(V7, "< 10%");
       }
}

void setup()
{
     Serial.begin(9600); 
      receptiondatacapteur.begin(9600);
    
   dht.begin();
 Wire.begin(D4 , D3);
   lcd.begin();
 lcd.setCursor(0,0);
   lcd.print("B");
   delay(300);
   lcd.setCursor(1,0);
   lcd.print("I");
   delay(300);
   lcd.setCursor(2,0);
   lcd.print("E");
   delay(300);
   lcd.setCursor(3,0);
   lcd.print("N");
   delay(300);
   lcd.setCursor(4,0);
   lcd.print("V");
   delay(300);
   lcd.setCursor(5,0);
   lcd.print("E");
   delay(300);
   lcd.setCursor(6,0);
   lcd.print("N");
   delay(300);
   lcd.setCursor(7,0);
   lcd.print("U");
   delay(300);
   lcd.setCursor(8,0);
   lcd.print("E");
   delay(300);

   lcd.setCursor(0,1);
   lcd.print("S");
     delay(300); 

     lcd.setCursor(1,1);
   lcd.print("T");
     delay(300);

      lcd.setCursor(2,1);
   lcd.print("A");
     delay(300); 

     lcd.setCursor(3,1);
   lcd.print("T");
     delay(300);

       lcd.setCursor(4,1);
   lcd.print("I");
     delay(300);

      lcd.setCursor(5,1);
   lcd.print("O");
     delay(300);

      lcd.setCursor(6,1);
   lcd.print("N");
     delay(300);

     lcd.setCursor(7,1);
   lcd.print(" ");
     delay(300);

      lcd.setCursor(8,1);
   lcd.print("M");
     delay(300);

       lcd.setCursor(9,1);
   lcd.print("E");
     delay(300);

      lcd.setCursor(10,1);
   lcd.print("T");
     delay(300);

      lcd.setCursor(11,1);
   lcd.print("E");
     delay(300);

      lcd.setCursor(12,1);
   lcd.print("O");
     delay(300);

   lcd.clear(); 

   lcd.setCursor(0,0); 
    lcd.print("STATION METEO");
    
     lcd.setCursor(0,1); 
    lcd.print("CHARGEMENT");
    
   for(int i = 0 ; i < 7 ; i++) { 
     lcd.setCursor(10+i,1);
      lcd.print("."); 
       delay(500);
   }

     lcd.clear();
  pinMode(echo , INPUT); 
   pinMode(trigger , OUTPUT); 
    pinMode(D0 , OUTPUT);

     pinMode(D8 , INPUT);

     lcd.setCursor(0,0);
      lcd.print("RECH.CONNEXION");

       lcd.setCursor(0,1);
        lcd.print("CLOUD BLYNK...");

  
//  Serial.println("Beginning Si1145!");
//  while (!SI1145.Begin())
//  {
//    Serial.println("Si1145 is not ready!");
//    delay(1000);
//  }
//  Serial.println("Si1145 is ready!");
//  myBarometer.init();
//  dht.begin();
//  delay(1000);
  Blynk.begin(auth, ssid, pass);
  lcd.clear();
   lcd.setCursor(0,0); 
    lcd.print("CONNECTER...");
  delay(1000);
    lcd.clear(); 
  timer.setInterval(1000L, sendSensor); // sendSensor function will run every 1000 milliseconds
}

void loop()
{
  Blynk.run();
  timer.run();
}
