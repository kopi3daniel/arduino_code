#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ArduinoJson.h>

// Identifiants du réseau WiFi
const char* ssid = "Meder";
const char* password = "dynastyRB";

// URL de la page web hébergée
const char* url = "https://medard-mak.github.io/sante/update.php";

// Objets pour les capteurs
Adafruit_BME280 bme;
int analogPin1 = 34;
int analogPin2 = 35;
int analogPin3 = 36;
int analogPin4 = 39;


void setup() {
  // Initialisation de la communication série
  Serial.begin(115200);

  // Connexion au réseau WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au WiFi...");
  }

  Serial.println("WiFi connecté !");

  // Initialisation des capteurs
  if (!bme.begin(0x76)) {
    Serial.println("Erreur lors de l'initialisation du capteur BME280 !");
    while (1);
  }
}

void loop() {
  // Lecture des valeurs des capteurs
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;
  int sensorValue1 = analogRead(analogPin1);
  int sensorValue2 = analogRead(analogPin2);
  int sensorValue3 = analogRead(analogPin3);
  int sensorValue4 = analogRead(analogPin4);

  // Création de l'objet JSON avec les valeurs des capteurs
  DynamicJsonDocument jsonDocument(256);
  jsonDocument["temperature"] = temperature;
  jsonDocument["humidity"] = humidity;
  jsonDocument["pressure"] = pressure;
  jsonDocument["sensorValue1"] = sensorValue1;
  jsonDocument["sensorValue2"] = sensorValue2;
  jsonDocument["sensorValue3"] = sensorValue3;
  jsonDocument["sensorValue4"] = sensorValue4;

  // Conversion de l'objet JSON en chaîne de caractères
  String jsonString;
  serializeJson(jsonDocument, jsonString);

  // Création d'une instance de la classe HTTPClient
  esHTTPClient http;

  // Envoi de la requête POST avec les données des capteurs
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(jsonString);

  // Vérification du code de réponse
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("Réponse du serveur : " + response);
  } else {
    Serial.println("Erreur lors de l'envoi de la requête POST !");
    Serial.print("Code d'erreur : ");
    Serial.println(httpResponseCode);
  }

  // Libération des ressources
  http.end();

  // Attente avant la prochaine lecture des capteurs
  delay(5000);
}
