#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL2Ujw1HkGS" // replace this with template id
#define BLYNK_TEMPLATE_NAME "AFRITECH" // replace this with your device name
#define BLYNK_AUTH_TOKEN   "QUxTc1wO7HNYqHYEb4dvTp6eZPzza2gE"

#include <ESP8266WiFi.h> // importing all the required libraries
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>


float temperature ; // parameters
float humiditee;
  



char auth[] = "QUxTc1wO7HNYqHYEb4dvTp6eZPzza2gE"; // replace this with your auth token
char ssid[] = "ing kopi3"; // replace this with your wifi name (SSID)
char pass[] = "1234567890"; // replace this with your wifi password


BlynkTimer timer;


void sendSensor() // function to read sensor values and send them to Blynk
{


    
//  humiditee = dht.readHumidity();
//   temperature = dht.readTemperature();
  humiditee = 44.80;
  temperature = 32.00;




  Blynk.virtualWrite(V0, temperature); // send all the values to their respective virtual pins
  Blynk.virtualWrite(V1, humiditee);

}

void setup()
{
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor); // sendSensor function will run every 1000 milliseconds
}

void loop()
{
  Blynk.run();
  timer.run();
}
