#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

const char *ssid = "irk";
const char *password = "1234567890";


SoftwareSerial NanoSerial(D1, D2);

//  String datatemperatureeau ; 
//  String dataPH
ESP8266WebServer server(80);
long temps;
float tm;
String dataIn;
String c;
int8_t indexOfA,indexOfB,indexOfC,indexOfD,indexOfE,indexOfF;
String data1,data2,data4,data5,data6,data3;

//float tm=0.00;
void setup() {
  Serial.begin(115200);
  NanoSerial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(F("erreur 2329"));
    delay(500);
  }
  server.on("/", handleRoot);
  server.begin();
  IPAddress myIP = WiFi.localIP();
  Serial.print(myIP);
   temps = millis();
}

void loop() {
 LecturaTH();
  server.handleClient();
}

// creamos la funcion Estructura HTML
void handleRoot() {
  server.send(200, "text/html", "<html><head><title>DASHBOARD DU PISCUCUTURE</title><meta name='viewport' content='width=device-width, initial-scale=1'>"
  "<link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.7.2/css/all.css' integrity='sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr' crossorigin='anonymous'>"
  "<link rel='icon' href='data:,'><style>"
    "html {font-family: Arial; display: inline-block; text-align: center;}  p {  font-size: 1.2rem;} body {  margin: 0;}"
    ".topnav { overflow: hidden; background-color: #1f71ff; color: white; font-size: 1.7rem; } .content { padding: 20px; }"
    ".card { background-color: white; box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5); }.cards { max-width: 700px; margin: 0 auto; display: grid; grid-gap: 2rem; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); }   .reading { font-size: 2.8rem; } .packet { color: #bebebe; }"
    ".card.temperature { color: #fd7e14; }  .card.humidity { color: #1b78e2; }  .card.temperature1 { color: #045c29; }  .card.humidity1 { color: #ff1919; }.card.temperature2 { color: #abfd14; } .card.humidity2 { color: #e21bb7; }"
  "</style></head><body>"
  "<div class='topnav'><h3>DASHBOARD DE LA PISCUCUTURE</h3></div><div class='content'><div class='cards'><div class='card temperature'>"
    "<h4><i class='fas fa-thermometer-half'></i>TEMPERATURE</h4><p><span class='reading'>"+ String(data6) + " &deg;C</span></p>"
    "</div><div class='card humidity'><h4><i class='fas fa-thermometer-half'></i>pH</h4><p><span class='reading'>"+ String(data1) + " pH</span></p>"
    "</div><div class='card temperature1'><h4><i class='fas fa-thermometer-half'></i> TDS</h4><p><span class='reading'>"+ String(data2) + " ppm</span></p> </div>"
    "<div class='card humidity1'><h4><i class='fas fa-thermometer-half'></i> EC</h4><p><span class='reading'>"+ String(data3) + " mv &sup2;</span></div>"
    "<div class='card humidity2'><h4><i class='fas fa-thermometer-half'></i> Litre</h4><p><span class='reading'> "+ String(data4) + " L</span></p></div>"
    "<div class='card temperature2'><h4><i class='fas fa-thermometer-half'></i> GAZ</h4><p><span class='reading'>"+ String(data5) + " m&sup3;</span></p></div>"
    "</div> </div><script></script></body></html>");
}

// funcion de lectura de temperatura y humedad
void LecturaTH() {
  if(NanoSerial.available()>0){
    c=NanoSerial.readString();

    

    // Serial.println("ph" +data1);
    // Serial.println("tds" +data2);
    // Serial.println("ec" +data3);
    // Serial.println("niveau" +data4);
    // Serial.println("gaz" +data5);
    Serial.println(c);
    
    Serial.println("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

  //   if(c=='\n'){
  //     break;
  //   }
  //   else {
  //   dataIn;
  //   }
  // }
  // if(c=='\n'){
  //   envoie_donner();
  //   c=0;
  //   dataIn=" ";
  }

}
