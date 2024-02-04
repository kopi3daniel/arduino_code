
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>

#include <EEPROM.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */


#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>



LiquidCrystal_I2C lcd(0X3F, 16, 2);
DHT dht(D5, DHT11);


float humiditedata, temperaturedata;

const char* ssid = "ing kopi3";
const char* password = "1234567890";

// IPAddress local_ip(192, 168, 2, 1);
// IPAddress gateway(192, 168, 2, 1);
// IPAddress subnet(255, 255, 255, 0);


char auth[] = "QUxTc1wO7HNYqHYEb4dvTp6eZPzza2gE"; // replace this with your auth token
 char sssid[] = "ing kopi3"; // replace this with your wifi name (SSID)
 char pass[] = "1234567890"; // replace this with your wifi password


 ESP8266WebServer server(80);
//WiFiServer server(80);

BlynkTimer timer;

int datalimitetemperature;

boolean lampeallumee;

void Modulesensor(){

  Blynk.virtualWrite(V0, humiditedata); // send all the values to their respective virtual pins
  Blynk.virtualWrite(V1, temperaturedata);
  


}


void setup() {


  dht.begin();
  Wire.begin(D3, D4);
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("BIENVENUE");

  lcd.setCursor(0, 1);
  lcd.print("AFRITECH sarl");

  delay(3000);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("AFRITECH sarl");

  lcd.setCursor(0, 1);
  lcd.print("CHARGEMENT");

  for (int i = 0; i < 7; i++) {
    lcd.setCursor(10 + i, 1);
    lcd.print(".");
    delay(500);
  }
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("AFRITECH sarl");

  lcd.setCursor(0, 1);
  lcd.print("T:");


  lcd.setCursor(10, 1);
  lcd.print("H:");

  Serial.println("HTTP server started");

  // WiFi.softAP(ssid, password);
  // WiFi.softAPConfig(local_ip, gateway, subnet);
  // delay(100);

  WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {

       Serial.println(F("erreur 2329"));
       delay(500);
      
    }

      
       
       
     Blynk.begin(auth, sssid, pass);
      
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");    // this is the address to use for viewing the map
    Serial.println(WiFi.localIP());
    server.begin();

  server.on("/", handle_OnConnect);


  server.on("/pompeon", handle_pompeon);
  server.on("/pompeoff", handle_pompeoff);

  server.on("/mangeoireaon", handle_mangeoireaON);
  server.on("/mangeoireaoff", handle_mangeoireaOFF);

  server.on("/mangeoirebon", handle_mangeoirebON);
  server.on("/mangeoireboff", handle_mangeoirebOFF);

  server.on("/mangeoirecon", handle_mangeoirecON);
  server.on("/mangeoirecoff", handle_mangeoirecOFF);

  server.on("/electrovanneaon", handle_electrovanneaON);
  server.on("/electrovanneaoff", handle_electrovanneaOFF);

  server.on("/electrovannebon", handle_electrovannebON);
  server.on("/electrovanneboff", handle_electrovannebOFF);


  server.on("/temp1", handle_choixtemperature1);
  server.on("/temp2", handle_choixtemperature2);
  server.on("/temp3", handle_choixtemperature3);


 server.onNotFound(handle_NotFound);

  server.begin();
timer.setInterval(1000L, Modulesensor);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);

  Serial.begin(115200);
}


void loop() {

  // humiditedata = dht.readHumidity();
  // temperaturedata = dht.readTemperature();

  humiditedata =25.79;
  temperaturedata = 22.00;

  

  Blynk.run();
  timer.run();

  Serial.println(datalimitetemperature);
  Serial.println(temperaturedata);

  if (datalimitetemperature == 0 && temperaturedata >= 34.50) {
    digitalWrite(D0, LOW);
  }
  if (datalimitetemperature == 0 && temperaturedata < 32.50) {
    digitalWrite(D0, HIGH);
  }

  if (datalimitetemperature == 1 && temperaturedata >= 38.50) {
    digitalWrite(D0, LOW);
  }
  if (datalimitetemperature == 1 && temperaturedata < 37.50) {
    digitalWrite(D0, HIGH);
  }

  if (datalimitetemperature == 2 && temperaturedata >= 34.50) {
    digitalWrite(D0, LOW);
  }
  if (datalimitetemperature == 2 && temperaturedata < 32.50) {
    digitalWrite(D0, HIGH);
  }

  if (datalimitetemperature == 3 && temperaturedata >= 30.50) {
    digitalWrite(D0, LOW);
  }
  if (datalimitetemperature == 3 && temperaturedata < 30.00) {
    digitalWrite(D0, HIGH);
  }




  if (temperaturedata < 100) {
    lcd.setCursor(2, 1);
    lcd.print(temperaturedata);
    lcd.print("  ");

    lcd.setCursor(12, 1);
    lcd.print(humiditedata);
    lcd.print("  ");
  }



  server.handleClient();
}

void handle_OnConnect() {
  server.send(200, "text/html", SendHTML(false));
}
void handle_pompeon() {

  lampeallumee = true;
  digitalWrite(D0, HIGH);
  lcd.setCursor(14, 0);
  lcd.print("AP");
  server.send(200, "text/html", SendHTML(true));
}
void handle_pompeoff() {

  lampeallumee = false;
  digitalWrite(D0, LOW);
  lcd.setCursor(14, 0);
  lcd.print("DP");
  server.send(200, "text/html", SendHTML(false));
}
void handle_NotFound() {

  server.send(404, "text/plain", "Not found");
}

void handle_mangeoireaON() {
  digitalWrite(D1, HIGH);
  lcd.setCursor(14, 0);
  lcd.print("AM");
  server.send(200, "text/html", SendHTML(true));
}

void handle_mangeoireaOFF() {
  digitalWrite(D1, LOW);
  lcd.setCursor(14, 0);
  lcd.print("DM");
  server.send(200, "text/html", SendHTML(false));
}


void handle_mangeoirebON() {
  digitalWrite(D2, HIGH);
  lcd.setCursor(14, 0);
  lcd.print("AM");
  server.send(200, "text/html", SendHTML(true));
}

void handle_mangeoirebOFF() {
  digitalWrite(D2, LOW);
  lcd.setCursor(14, 0);
  lcd.print("DM");
  server.send(200, "text/html", SendHTML(false));
}


void handle_mangeoirecON() {
  digitalWrite(D6, HIGH);
  lcd.setCursor(14, 0);
  lcd.print("AM");
  server.send(200, "text/html", SendHTML(true));
}

void handle_mangeoirecOFF() {
  digitalWrite(D6, LOW);
  lcd.setCursor(14, 0);
  lcd.print("DM");
  server.send(200, "text/html", SendHTML(true));
}

void handle_electrovanneaON() {
  digitalWrite(D7, HIGH);
  lcd.setCursor(14, 0);
  lcd.print("EA");
  server.send(200, "text/html", SendHTML(false));
}


void handle_electrovanneaOFF() {
  digitalWrite(D7, LOW);
  lcd.setCursor(14, 0);
  lcd.print("DE");
  server.send(200, "text/html", SendHTML(true));
}




void handle_electrovannebON() {
  digitalWrite(D8, HIGH);
  lcd.setCursor(14, 0);
  lcd.print("AE");
  server.send(200, "text/html", SendHTML(false));
}


void handle_electrovannebOFF() {
  digitalWrite(D8, LOW);
  lcd.setCursor(14, 0);
  lcd.print("DE");
  server.send(200, "text/html", SendHTML(true));
}

void handle_choixtemperature1() {

  // eeprom.write(0x34 , 1);

  datalimitetemperature = 1;
  lcd.setCursor(14, 0);
  lcd.print("TA");
  server.send(200, "text/html", SendHTML(true));
}

void handle_choixtemperature2() {

  //eeprom.write(0x34 , 2);

  datalimitetemperature = 2;
  lcd.setCursor(14, 0);
  lcd.print("TB");
  server.send(200, "text/html", SendHTML(true));
}

void handle_choixtemperature3() {

  // eeprom.write(0x34 , 3);

  datalimitetemperature = 3;
  lcd.setCursor(14, 0);
  lcd.print("TC");
  server.send(200, "text/html", SendHTML(true));
}




String SendHTML(uint8_t led) {
  String ptr = "<!DOCTYPE html>\n";

  ptr += "<html>\n";
  ptr += "<head>\n";
  ptr += "<body  style=\"background: powderblue\">";

  ptr += " <meta charset = \"utf-8\"/>";

  ptr += " <meta http-equiv = \"refresh\"  content = \"3\"  />";

  ptr += "<h1  align=\"center\" > AFRITECH CONTROLER </h1>";

  ptr += "<table  width=\"800\"  height = \"50\" border=\"20\" align=\"center\"> ";
  ptr += "<caption> <h1> DATA TEMPERATURE & HUMIDITE  </h1> </caption>";

  ptr += "<tr>";

  ptr += "<td align =\"center\"> TEMPERATURE </td>";
  ptr += "<td align =\"center\"> HUMIDITE </td>";

  ptr += "</tr>";

  ptr += "<tr>";

  ptr += " <td align =\"center\">";
  ptr += "<h1>";
  ptr += temperaturedata;
  ptr += "</h1>";
  ptr += "</td>";

  ptr += " <td align =\"center\">";
  ptr += "<h1>";
  ptr += humiditedata;
  ptr += "</h1>";
  ptr += "</td>";


  ptr += "</tr>";
  ptr += "</table>";



  ptr += "<table  width=\"800\"  height = \"50\" border=\"20\" align=\"center\">";
  ptr += "<caption> <h1> CHOIX TEMPERATURE </h1> </caption>";

  ptr += "<tr>";
  ptr += " <td align=\"center\"> CHOIX TEMP. </td>";
  ptr += "<td align=\"center\"> CHOIX TEMP. </td>";
  ptr += "</tr>";

  ptr += "<tr>";
  ptr += "<td align=\"center\"> <a href=\"/temp1\"\"> <button  style=\"background-color: yellow ; width:100px ; height:100px ;border-radius:100px\" > 38.50 </button> </a> </td>";
  ptr += " <td align=\"center\"> <a href=\"/temp2\"\"><button style= \"background-color: yellow ; width:100px ; height:100px ;border-radius:100px\"> 32.50 </button> </a> </td>";
  ptr += "</tr>";


  ptr += "<tr>";
  ptr += "<td align=\"center\"> <a href=\"/temp3\"\"> <button  style=\"background-color: yellow ; width:100px ; height:100px ;border-radius:100px\" > 30.50 </button> </a> </td>";

  if (datalimitetemperature == 0) {
    ptr += " <td align=\"center\"> .......... </td>";
  }

  if (datalimitetemperature == 1) {
    ptr += " <td align=\"center\"> 38.50 </td>";
  }

  if (datalimitetemperature == 2) {
    ptr += " <td align=\"center\"> 34.50 </td>";
  }

  if (datalimitetemperature == 3) {
    ptr += " <td align=\"center\"> 30.50 </td>";
  }


  ptr += "</tr>";


  ptr += "</table>";


  ptr += "<table  width=\"800\"  height = \"50\" border=\"20\" align=\"center\">";

  ptr += "<caption> <h1> CONTROLE POMPE </h1> </caption>";

  ptr += "<tr>";
  ptr += " <td align=\"center\"> POMPE </td>";
  ptr += "<td align=\"center\"> INST.</td>";
  ptr += "</tr>";

  ptr += "<tr>";
  ptr += "<td align=\"center\"> <a href=\"/mangeoirebon\"\"> <button  style=\"background-color: green ; width:100px ; height:100px ;border-radius:100px\" > ON </button> </a> </td>";
  ptr += " <td align=\"center\"> <a href=\"/mangeoireboff\"\"> <button style= \"background-color: red ; width:100px ; height:100px ;border-radius:100px\"> OFF </button> </a> </td>";
  ptr += "</tr>";

  ptr += "</table>";


  // ptr += "<table  width=\"800\"  height = \"50\" border=\"20\" align=\"center\">";
  //  ptr += "<caption> <h1> CONTROLE LAMPE CHAUFFANTE  </h1> </caption>";
  //
  //  ptr += "<tr>";
  //   ptr += " <td align=\"center\"> CHAUFF. </td>";
  //    ptr += "<td align=\"center\"> INST.</td>";
  //  ptr += "</tr>";
  //
  //   ptr += "<tr>";
  //   ptr += "<td align=\"center\"> <a href=\"/pompeon\"\"> <button  style=\"background-color: green ; width:100px ; height:100px ;border-radius:100px\" > ON </button> </a> </td>";
  //    ptr += " <td align=\"center\"> <a href=\"/pompeoff\"\"><button style= \"background-color: red ; width:100px ; height:100px ;border-radius:100px\"> OFF </button> </a> </td>";
  //  ptr += "</tr>";
  //
  //  ptr += "</table>";


  ptr += "<table  width=\"800\"  height = \"50\" border=\"20\" align=\"center\">";
  ptr += "<caption> <h1> CONTROLE ELECTROVANNE A </h1> </caption>";

  ptr += "<tr>";
  ptr += " <td align=\"center\"> ELV.A </td>";
  ptr += "<td align=\"center\"> INST.</td>";
  ptr += "</tr>";

  ptr += "<tr>";
  ptr += "<td align=\"center\"> <a href=\"/electrovanneaon\"\"> <button  style=\"background-color: green ; width:100px ; height:100px ;border-radius:100px\" > ON </button> </a> </td>";
  ptr += " <td align=\"center\"> <a href=\"/electrovanneaoff\"\"> <button style= \"background-color: red ; width:100px ; height:100px ;border-radius:100px\"> OFF </button> </a> </td>";
  ptr += "</tr>";

  ptr += "</table>";




  ptr += "<table  width=\"800\"  height = \"50\" border=\"20\" align=\"center\">";

  ptr += "<caption> <h1> CONTROLE ELECTOVANNE B </h1> </caption>";

  ptr += "<tr>";
  ptr += " <td align=\"center\"> ELV.B </td>";
  ptr += "<td align=\"center\"> INST.</td>";
  ptr += "</tr>";

  ptr += "<tr>";
  ptr += "<td align=\"center\"> <a href=\"/electrovannebon\"\"> <button  style=\"background-color: green ; width:100px ; height:100px ;border-radius:100px\" > ON </button> </a> </td>";
  ptr += " <td align=\"center\"> <a href=\"/electrovanneboff\"\"> <button style= \"background-color: red ; width:100px ; height:100px ;border-radius:100px\"> OFF </button> </a> </td>";
  ptr += "</tr>";

  ptr += "</table>";


  ptr += "<table  width=\"800\"  height = \"50\" border=\"20\" align=\"center\">";

  ptr += "<caption> <h1> CONTROLE MANGEOIRE A </h1> </caption>";

  ptr += "<tr>";
  ptr += " <td align=\"center\"> ELV.B </td>";
  ptr += "<td align=\"center\"> INST.</td>";
  ptr += "</tr>";

  ptr += "<tr>";
  ptr += "<td align=\"center\"> <a href=\"/mangeoireaon\"\"> <button  style=\"background-color: green ; width:100px ; height:100px ;border-radius:100px\" > ON </button> </a> </td>";
  ptr += "<td align=\"center\"> <a href=\"/mangeoireaoff\"\"> <button style= \"background-color: red ; width:100px ; height:100px ;border-radius:100px\"> OFF </button> </a> </td>";
  ptr += "</tr>";

  ptr += "</table>";




  ptr += "<table  width=\"800\"  height = \"50\" border=\"20\" align=\"center\">";

  ptr += "<caption> <h1> CONTROLE MANGEOIRE B </h1> </caption>";

  ptr += "<tr>";
  ptr += " <td align=\"center\"> ELV.B </td>";
  ptr += "<td align=\"center\"> INST.</td>";
  ptr += "</tr>";

  ptr += "<tr>";
  ptr += "<td align=\"center\"> <a href=\"/mangeoirecon\"\"> <button  style=\"background-color: green ; width:100px ; height:100px ;border-radius:100px\" > ON </button> </a> </td>";
  ptr += " <td align=\"center\"> <a href=\"/mangeoirecoff\"\"> <button style= \"background-color: red ; width:100px ; height:100px ;border-radius:100px\"> OFF </button> </a> </td>";
  ptr += "</tr>";

  ptr += "</table>";

  ptr += "<table  width=\"800\"  height = \"50\" border=\"20\" align=\"center\">";

  ptr += "<caption> <h1> CONTROLE MANGEOIRE C </h1> </caption>";

  ptr += "<tr>";
  ptr += " <td align=\"center\"> ELV.B </td>";
  ptr += "<td align=\"center\"> INST.</td>";
  ptr += "</tr>";

  ptr += "<tr>";
  ptr += "<td align=\"center\"> <a href=\"/mangeoirebon\"\"> <button  style=\"background-color: green ; width:100px ; height:100px ;border-radius:100px\" > ON </button> </a> </td>";
  ptr += " <td align=\"center\"> <a href=\"/mangeoireboff\"\"> <button style= \"background-color: red ; width:100px ; height:100px ;border-radius:100px\"> OFF </button> </a> </td>";
  ptr += "</tr>";

  ptr += "</table>";


  ptr += "</body>\n";
  ptr += "</html>\n";

  return ptr;
}