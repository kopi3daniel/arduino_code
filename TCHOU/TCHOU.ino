#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>



const char *ssid = "ir";
const char *password = "1234567890";


float temperature;
float temperatureseuil;

 
float t2;
float h2;
float f2;

float t1;
float h1;
float f1;

float tm;
float hm;
float fm;

ESP8266WebServer server(80);




#include "DHT.h"




#define DHTPIN D6
#define DHTPIN1 D3

#define DHTTYPE DHT22

#define capteur_moteur1 D4
#define capteur_moteur2 D5

#define moteur1 D0
#define moteur2 D7

#define relaisTemperature D8


DHT dht(DHTPIN, DHTTYPE);
DHT dht1(DHTPIN1, DHTTYPE);

long temps;
void setup() {
  Serial.begin(115200);

  // Wire.begin(D3,D4); // SDA y SCL
  Serial.println(F("DHTxx test!"));


  dht.begin();
  dht1.begin();

  pinMode(relaisTemperature, OUTPUT);
  pinMode(moteur1, OUTPUT);

  pinMode(moteur2, OUTPUT);
  pinMode(capteur_moteur2, INPUT);
  pinMode(capteur_moteur1, INPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(F("erreur 2329"));
    lcd.setTextSize(2);  // taille du texte
    lcd.setTextColor(WHITE);
    lcd.setCursor(0,0);
    lcd.print("err 2329");


    delay(500);
    lcd.clearlcd();


    delay(300);
  }
  lcd.setTextSize(2);  // taille du texte
  lcd.setTextColor(WHITE);
  lcd.setCursor(10, 0);  // position du curseur colonne / ligne
  lcd.print("I.I.T.A");
  lcd.setTextSize(1);
  lcd.setCursor(0, 25);
  lcd.println("Chargement");
  for (int i = 0; i < 73; i++) {
    lcd.setCursor(10 + i, 0);

lcd.clear();    
    lcd.print(".");

    delay(100);
  }
  lcd.clear();
  server.on("/", handleRoot);
  server.begin();
  lcd.setCursor(0,0);
  lcd.print("MALIKIYA_X HTTP OK...");
  delay(5000);
  lcd.clearlcd();
  lcd.setCursor(0, 1);
  lcd.print("AFRITECH HTTP OK...");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 1);
  IPAddress myIP = WiFi.localIP();
  lcd.print("IP: ");
  lcd.print(myIP);
  Serial.print(myIP);
  delay(5000);
  lcd.clear();


  temps = millis();
}

void loop() {



temperatureseuil=temperature-2.00;
  
  
  lcd.setCursor(0, 0);
  lcd.print("Temp moyen:");
  lcd.print(tm);
  lcd.print("'C");
  lcd.println(" ");
  lcd.setCursor(1,0);
  lcd.print("Hum moyen:");
  lcd.print(hm);
  lcd.print("%");
  lcd.println(" ");
  delay(2000);
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("Temp max: ");
  lcd.print(temperature);
  lcd.print("'C");
  lcd.println(" ");
  lcd.setCursor(10,30);
  lcd.print("Temp min: ");
  lcd.print(temperatureseuil);
  lcd.print("'c");
  lcd.println(" ");

  if (digitalRead(capteur_moteur1) == LOW) {
    digitalWrite(moteur1, HIGH);
  } else {
    digitalWrite(moteur1, LOW);
  }
  if (digitalRead(capteur_moteur2) == LOW) {
    digitalWrite(moteur2, HIGH);
  } else {
    digitalWrite(moteur2, LOW);
  }

  if (tm>temperature) {
  digitalWrite(relaisTemperature,HIGH );
  }

  if(tm<temperatureseuil){
    digitalWrite(relaisTemperature,LOW);
  }
  if ((millis() - temps) > 2000) {
    temps = millis();

    lcd.clearlcd();
  }


  LecturaTH();
  server.handleClient();
}

// creamos la funcion Estructura HTML
void handleRoot() {
  server.send(200, "text/html", "<html><head> <meta charset='UTF-8'> <meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1.'>"
                                "<title>Controleur poussin</title></head>  "
                                "<style>@import url('https://fonts.googleapis.com/css2?family=Poppins&lcd=swap');*{padding: 0;margin: 0; font-family: 'Poppins',sans-serif;}"
                                "body {font-family: monospace;background-color: rgb(20,21, 38);}.container{width: 80%;margin: 80px auto;}  "
                                ".container h1{padding: 60px 0; color: #fff; font-size: 44px; text-align: center;}  "
                                ".row{ lcd: flex;align-items: center;flex-wrap: wrap;}.col{ flex-basis: 50%; min-width: 250px;}"
                                ".feature-img{width: 83%; margin: auto; position: relative; border-radius: 6px; overflow: hidden;}"
                                ".small-img-row{ lcd: flex; background: #efefef; margin: 20px 0; align-items: center; border-radius: 6px; overflow: hidden; width: 85%;}"
                                ".small-img{ position: relative;}"
                                ".small-img img{  width: 150px;}"
                                ".small-img-row p{ margin-left: 20px;color: hsl(143, 55%, 45%);line-height: 22px;font-size: 15px;}.play-btn{width: 60px;position: absolute;left: 50%;top: 50%;transform: translate(-50%,-50%);cursor: pointer;}  "
                                ".small-img .play-btn{width: 35px;}  "
                                ".video-player{width: 80%; position: absolute;left: 50%; top: 50%; transform: translate(-50%,-50%); cursor: pointer; lcd: none;}video:focus{ outline: none;}  "
                                ".close-btn{ position: absolute; top: 10px; right: 10px; width: 30px; cursor: pointer;}  "

                                " {color: white;text-align: center;margin: 50px;font-size: 18px;}  "
                                ".barraTemp{height: 200px;width: 200px;margin: auto;border-radius: 50%;overflow: hidden;}  "
                                ".cont{height: 100px;width: 200px;}  "
                                ".circulo_centro {width: 150px;height: 150px;background-color: rgb(20,21, 38);border-radius: 50%;margin: auto;position: relative;margin: -175px auto 50px;}  "
                                ".rectangulo{width: 200px;height: 100px;background-color: rgb(20,21, 38);position: relative;margin: -125px auto 50px;}</style>  "
                                "<body><div class='container'><h1>les video de surveillances</h1><div class='row'><div class='small-img-row'><div class='small-img'>  <img src='https://www.regal-basse-cour.com/wp-content/uploads/2022/12/AdobeStock_450760628-bd.jpg' alt="
                                ">"
                                " <img src='https://static.vecteezy.com/system/resources/previews/018/887/460/non_2x/signs-close-icon-png.png'class='play-btn'  button onclick='window.location.href = 'http://192.168.43.1';'></div><p>surveillances  sur les poussin</p>"
                                "</div><div class='small-img-row'><div class='small-img'><img src='https://www.woopets.fr/assets/img/010/161/1200x675/loi-poules-poulailler.jpg' alt="
                                ">"
                                "<img src='https://static.vecteezy.com/system/resources/previews/018/887/460/non_2x/signs-close-icon-png.png'class='play-btn' button onclick='window.location.href = 'http://192.168.43.4';'></div><p>surveillances poules</p></div>  "
                                "<div class='col'></div></div></div><div class='video-player' id='videoplayer'><video  width='100%' controls autoplay id='myvideo'>  "
                                "<source src='car.mp4' type='video/mp4' ></video><img src='https://static.vecteezy.com/system/resources/previews/018/887/460/non_2x/signs-close-icon-png.png' class='close-btn' onclick='stopbtn()'></div>  "
                                
                                "<div class='container'><h1>Evolue de la temperature en fonctions <br>de resistances chauffante</h1>  "
                                // "<div class='container"><h1>Evolue de la temperature en fonctions <br>de resistances chauffante</h1>
                                "<h1>temperature</h1>"

                                "<div class='barraTemp' style='transform: rotate("
                                  + String(map(tm, 0, 100, 0, 180)) + "deg);'>"
                                                                      "<div class='cont' style='background-color: rgb(59, 226, 255);'></div>"
                                                                      "<div class='cont' style='background-color: rgb(253, 0, 0);'></div>"

                                                                      "</div>"
                                                                      "<div class='circulo_centro'></div>"
                                                                      "<div class='rectangulo'></div>"
                                                                      "<h1 style='font-size: 22px; position: relative; margin: -125px auto 50px;'>"
                                  + String(tm) + " °C</h1>"

                                  "<h1>temperature max</h1>"

                                "<div class='barraTemp' style='transform: rotate("
                                  + String(map(temperature, 0, 100, 0, 180)) + "deg);'>"
                                                                      "<div class='cont' style='background-color: rgb(59, 226, 255);'></div>"
                                                                      "<div class='cont' style='background-color: rgb(253, 0, 0);'></div>"

                                                                      "</div>"
                                                                      "<div class='circulo_centro'></div>"
                                                                      "<div class='rectangulo'></div>"
                                                                      "<h1 style='font-size: 22px; position: relative; margin: -125px auto 50px;'>"
                                  + String(temperature) + " °C</h1>"

                                  "<h1>temperature min</h1>"

                                "<div class='barraTemp' style='transform: rotate("
                                  + String(map(temperatureseuil, 0, 100, 0, 180)) + "deg);'>"
                                                                      "<div class='cont' style='background-color: rgb(59, 226, 255);'></div>"
                                                                      "<div class='cont' style='background-color: rgb(253, 0, 0);'></div>"

                                                                      "</div>"
                                                                      "<div class='circulo_centro'></div>"
                                                                      "<div class='rectangulo'></div>"
                                                                      "<h1 style='font-size: 22px; position: relative; margin: -125px auto 50px;'>"
                                  + String(temperatureseuil) + " °C</h1>"

                                                 "<h1>Hymidite</h1>"
                                                 "<div class='barraTemp' style='transform:rotate("
                                  + String(map(hm, 0, 100, 0, 180)) + "deg);'>"
                                                                      "<div class='cont' style='background-color: rgb(56, 3, 248);'></div>"
                                                                      "<div class='cont' style='background-color: rgb(255, 7, 131);'></div> "

                                                                      "</div>"
                                                                      "<div class='circulo_centro'></div>"
                                                                      "<div class='rectangulo'></div>"
                                                                      "<h1 style='font-size: 22px; position: relative; margin: -125px auto 50px;'>"
                                  + String(hm) + " °C</h1>"
                                                 "</div>"

                                                 

                                                 "<script>"

                                                 "var videoplayer = document.getElementById('videoplayer');"
                                                 "var myvideo = document.getElementById('myvideo');"

                                                 "function stopbtn(){videoplayer.style.lcd = 'none';}"
                                                 "function playVideo(file){myvideo.src = file;videoplayer.style.lcd = 'block';}"
                                                 "</script>"
                                                 "</body>"
                                                 "</html>");
}

// funcion de lectura de temperatura y humedad
void LecturaTH() {

  h1 = dht.readHumidity();
  t1 = dht.readTemperature();
  f1 = dht.readTemperature(true);
  h2 = dht1.readHumidity();
  t2 = dht1.readTemperature();
  f2 = dht1.readTemperature(true);

  hm = (h1 + h2) / 2;
  tm = (t1 + t2) / 2;

  // Check if any reads failed and exit early (to try again).
  if (isnan(h1) || isnan(t1) || isnan(f1)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  if (isnan(h2) || isnan(t2) || isnan(f2)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif2 = dht.computeHeatIndex(f1, h1);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic2 = dht.computeHeatIndex(t1, h1, false);

  // Compute heat index in Fahrenheit (the default)
  float hif1 = dht.computeHeatIndex(f2, h2);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic1 = dht.computeHeatIndex(t2, h2, false);

  Serial.print(F("Humidity: "));
  Serial.print(hm);

  Serial.print(F("%  Temperature: "));
  Serial.print(tm);
  Serial.print(F("°C "));
  Serial.print(F("temperature max: "));
  Serial.print(temperature);

  Serial.print(F("%  Temperature min: "));
  Serial.print(temperatureseuil);
  Serial.print(F("°C "));
  Serial.print(fm);

  Serial.print(F("°F  Heat index: "));
  Serial.print(hic1);
  Serial.print(F("°C "));
  Serial.print(hif1);
  Serial.print(F("°F"));
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic2);
  Serial.print(F("°C "));
  Serial.print(hif2);
  Serial.println(F("°F"));

  temperature=analogRead(A0)/10.23;


  // imprimir datos en lcd
}


