#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


#define trig D5
#define echo D6

#define led_Jaune D7
#define led_Verte D0
#define buzz D1


#define capteurinfra D2

const char* ssid = "boite";
const char* password = "1234567890";
LiquidCrystal_I2C lcd(0x27, 16, 2);
int nombre1;
String page = "";

ESP8266WebServer server(80);

void configurationbalise() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}


boolean obstacledevant() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long distanceobstacledevant = pulseIn(echo, HIGH) / 58;
  Serial.println(distanceobstacledevant);

  if (distanceobstacledevant < 3) {
    return true;
  } else {
    return false;
  }
}


void setup() {
  configurationbalise();
  pinMode(capteurinfra, INPUT);

  pinMode(led_Jaune, OUTPUT);
  pinMode(led_Verte, OUTPUT);
  pinMode(buzz,OUTPUT);

  Wire.begin(D3, D4);
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("BOITE A LETTRE");

  //Serial.begin(9600);

  lcd.setCursor(0, 1);
  lcd.print("CHARGEMENT");

  for (int i = 0; i < 7; i++) {
    lcd.setCursor(10 + i, 1);
    lcd.print(".");
    delay(500);
  }
  lcd.clear();

  Serial.begin(115200);
  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   lcd.setCursor(0, 1);
  //   lcd.print("NON CONNECTER   ");
  //   delay(500);
  //   Serial.print(".");
  //   lcd.clear();
  //   lcd.print(".");
  // }


  lcd.setCursor(0, 0);
  WiFi.softAP(ssid, password);
  lcd.print("BOITE A LETTRE");
  Serial.println(WiFi.localIP());
  server.on("/", []() {
    page = "<html><head><title>Boite a lettre</title></head><style type=\"text/css\">";
    page += "table{border-collapse: collapse;}th {background-color:  green ;color: white;}table,td {border: 4px solid black;font-size: x-large;";
    page += "text-align:center;border-style: groove;border-color: black(255,0,0);}</style><body><center>";
    page += "<h1>Boite a lettre</h1><br><br><table style=\"width: 1200px;height: 450px;\"><tr>";
    page += "<th>Parametres</th><th>Valeur</th></tr><tr><td>nombre de lettte</td><td>" + String(nombre1) + "</td></tr>";
    page += "<meta http-equiv=\"refresh\" content=\"3\">";
    server.send(200, "text/html", page);
  });
  server.begin();
  IPAddress myIP = WiFi.softAPIP();
  Serial.print(myIP);
}

void loop() {
  server.handleClient();



  if (obstacledevant() == true) {
    digitalWrite(led_Jaune,HIGH);
    digitalWrite(buzz,HIGH);
    //delay(2000);
    // for(int i; i<10;i++){
    //   digitalWrite(led_Jaune,HIGH);
    //   delay(200);
    //   digitalWrite(led_Jaune,LOW);
    //   delay(200);

    // }igitalWrite(led_Jaune,HIGH);
    //
    if (digitalRead(capteurinfra) == LOW) {
      delay(2000);
      nombre1++;
      lcd.setCursor(0, 1);
      lcd.print(nombre1);
      lcd.print(" imepokelewa");
      delay(2000);
    }



    else {
      lcd.setCursor(2, 1);
      lcd.print("              ");
    }


  } else {

    digitalWrite(led_Jaune, LOW);
    digitalWrite(buzz, LOW);

  }

  if (nombre1 >= 1) {
    digitalWrite(led_Verte, HIGH);
  } else {
    digitalWrite(led_Verte, LOW);
  }
}
