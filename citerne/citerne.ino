#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "citerne";
const char *password = "1234567890";


#define  trigger D3 
#define  echo    D2


#define pompe D5
#define led_vert D7
#define led_jaune D8

ESP8266WebServer server(80);

long distanceobstacle,niveau_citerne;


void setup() {
  Serial.begin(115200);
  pinMode(trigger , OUTPUT); 
  pinMode(led_jaune, OUTPUT); 
  pinMode(led_vert , OUTPUT);
  pinMode(pompe , OUTPUT);

  pinMode(echo , INPUT);

  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   Serial.println(F("erreur 2329"));
  //   delay(500);
  // }
  WiFi.softAP(ssid, password);
  server.on("/", handleRoot);
  server.begin();

  //IPAddress myIP = WiFi.localIP();
  IPAddress myIP = WiFi.softAPIP();
  Serial.print(myIP);
  
}

void loop() {
 LecturaTH();
  server.handleClient();
}

// creamos la funcion Estructura HTML
void handleRoot() {
  server.send(200, "text/html","<html><head><meta name='viewport' content='width=device-width, user-scalable=no'> <meta http-equiv='refresh' content='5' charset='UTF-8'>"
    "<title>controleur </title><style>body {font-family: monospace;  background-color: rgb(70, 73, 121); }"
     "h1 {color: white; text-align: center;  margin: 50px;  font-size: 18px; }.barraTemp{height: 200px;width: 200px;margin: auto;"
    "border-radius: 50%; overflow: hidden; }.cont{height: 100px;width: 200px;}.circulo_centro {width: 150px;height: 150px;"
    "background-color: rgb(70, 73, 121);border-radius: 50%;margin: auto;position: relative;margin: -175px auto 50px;}.rectangulo{width: 200px;height: 100px; background-color: rgb(70, 73, 121);"
    "position: relative;margin: -125px auto 50px;}</style></head><body><h1>controleur </h1> <h1>niveau de l'eau</h1><div class='barraTemp' style='transform: rotate("+String(map(distanceobstacle,22,4,0,180))+"deg);'>"
    "<div class='cont' style='background-color: rgb(7, 52, 255);'></div><div class='cont' style='background-color: rgb(0, 253, 135);'></div>"
    "</div><div class='circulo_centro'></div><div class='rectangulo'></div><h1 style='font-size: 22px; position: relative; margin: -125px auto 50px;'>"+String(niveau_citerne)+" %</h1></body></html> ");
}

// funcion de lectura de temperatura y humedad
void LecturaTH() {
digitalWrite(trigger , LOW);
            delayMicroseconds(2); 
             digitalWrite(trigger , HIGH);
            delayMicroseconds(10);
             digitalWrite(trigger , LOW);

             niveau_citerne=map(distanceobstacle,23,5,0,100);

             if(niveau_citerne>95){
                digitalWrite(led_jaune,HIGH);
                digitalWrite(pompe,HIGH );
                Serial.print("  pompe off ");

              }
              if(niveau_citerne<50){
                digitalWrite(led_jaune,LOW);
                digitalWrite(led_vert,HIGH);
                digitalWrite(pompe,LOW );
                Serial.print("  pompe on   ");

              }
             

              distanceobstacle = pulseIn(echo , HIGH)/58; 
              if(niveau_citerne<0){
                niveau_citerne=0;
              }

              


              // else{
              //     digitalWrite(led_vert,LOW);
              //     digitalWrite(led_jaune,LOW);
              //     digitalWrite(pompe,LOW );
              //     Serial.print(" normal   ");
              // }

              Serial.print("distance");
              Serial.print(distanceobstacle);
              Serial.print("            citerne");
              Serial.println(niveau_citerne);
              Serial.println(":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
              //delay(200);




}
