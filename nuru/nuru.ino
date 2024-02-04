
#include <Wire.h>
//#include <SoftwareSerial.h>
#include <TinyGPS++.h> 
#include <WiFi.h>


//SoftwareSerial Serial1(D6 , D5 );
TinyGPSPlus gps;
             
const char *ssid = "top";
const char *password = "1234567890";

String GMAP_API_KEY = "AIzaSyAVPiL9od4SIny5rlkOgrPgDEmLgYjcQO8";

WiFiServer server(80);

 String VALEURLIMITECOMMUNE = "-1.675138";
 

String html;

void setup(){

 
   pinMode(19 , OUTPUT);
    digitalWrite(19 , HIGH); 
    delay(2000);
    digitalWrite(19 , LOW); 
    
         
  Serial.begin(115200);
  Serial.println();
  Serial1.begin(9600);

    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {

       digitalWrite(19 , HIGH); 
    delay(400);
    digitalWrite(19 , LOW); 
        delay(400);
        Serial.print(".");
      
    }

      digitalWrite(19 , LOW); 
       delay(200); 
       
       
    
      
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");    // this is the address to use for viewing the map
    Serial.println(WiFi.localIP());
    server.begin();
   
  pinMode(18 , INPUT);
}

 int perdu; 

  boolean detgps=false;

void loop(){

   if(digitalRead(18) == LOW) { 
     perdu = perdu + 1;
     delay(400);
      digitalWrite(5 , HIGH);
   }

    
      Serial.println("WiFi connected");
  smartdelay_gps(1000);
   
  if (gps.location.isValid()) {



         if(digitalRead(18) == LOW) { 
     perdu = perdu + 1;
     delay(400);
      digitalWrite(5 , HIGH);
   }
   

   
    String latitude = String(gps.location.lat(), 6);
    String longitude = String(gps.location.lng(), 6); 

   Serial.print ("data longitude : ");
   Serial.println (longitude);   
 

   Serial.print("data latitude : ");
   Serial.println (latitude); 
   
    WiFiClient client = server.available();
    
    if(client) {                             
    Serial.println("new client");          
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            
      if (client.available()) {             // if there's client data
        char c = client.read();          // read a byte
          if (c == '\n') {                      // check for newline character,
          if (currentLine.length() == 0) {  // if line is blank it means its the end of the client HTTP request
      
    //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
    html="<!DOCTYPE html>";
    html+="<html lang='en'>";
    html+="<head>";
    html+="<meta charset='UTF-8'>";
    html+="<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html+="<meta http-equiv='X-UA-Compatible' content='ie=edge'>";
    html+="<title> localisation gps aveugle</title>";
    html+="<style>#map{height:600px;width:100%;}</style>";
    html+="</head>";
    html+="<body>";
    html+="<h1> Localisation Gps Aveugle  </h1>";
    html+="<div id='map'></div>";
    html+="<script>";
    //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
    
    html+="var map;";
    html+="var marker;";
    
    //5000ms means 5000/1000 = 5 Seconds
    //20000ms means 20000/1000 = 20 Seconds
    html+="var INTERVAL = 5000;";
    
    //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
    html+="function initMap(){";
      //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
      html+="var options = {";
          html+="zoom:16,";
          html+="center:{lat:"+latitude+",lng:"+longitude+"},";
          html+="mapTypeId: google.maps.MapTypeId.ROADMAP,";
      html+="};";
      //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
      html+="map = new google.maps.Map(document.getElementById('map'), options);";
    html+="}";
    //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM

    //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
    html+="function getMarkers() {";
      //html+="console.log("+latitude+");";
      //html+="console.log("+longitude+");";
      
      html+="var newLatLng = new google.maps.LatLng("+latitude+", "+longitude+");";
      //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
      html+="marker = new google.maps.Marker({";
        html+="position: newLatLng,";
        html+="map: map";
      html+="});";
      //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
    html+="}";
    //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM

    //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
    html+="window.setInterval(getMarkers,INTERVAL);";
    
    html+="</script>";
    html+="<script async defer src='https://maps.googleapis.com/maps/api/js?key="+GMAP_API_KEY+"&callback=initMap'>";
    html+="</script>";
    html+= "<h6> LONGITUDE=";
    html+= "<mark>";
    html+= longitude; 
     html+= "</mark>"; 
    html+= "</h6>";
    html+= "<h6> LATITUDE_=";
    html+= "<mark>";
    html+= latitude;
    html+= "</mark>"; 
    html+= "</h6>";

     if(perdu > 0) { 
       html+= "<p align=\"center\">  <button style=\"background-color: red ; width:100% ; height:150px ;border-radius:10px\"> <h1>AVEUGLE PERDU </h1> <p>";
     }

     if (perdu == 0) { 
             html+= "<p align=\"center\">  <button style=\"background-color: green  ; width:100% ; height:150px ;border-radius:10px\"> <h1> SUIVIE... </h1> <p>";

     }
    html+="</body></html>";
    //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
 
 client.print(html);

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {   currentLine = ""; }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c; // add it to the end of the currentLine
        }
         // here you can check for any keypresses if your web server page has any
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
    }    
  }
}

static void smartdelay_gps(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (Serial1.available())
      gps.encode(Serial1.read());
  } while (millis() - start < ms);
}

