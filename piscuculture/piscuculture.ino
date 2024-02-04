
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 32  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 4  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define SensorPin A0
float calibration_value = 21.34 + 0.7;
unsigned long int avgValue;
int buf[10], temp;

float rawEc, temperatureCoefficient, phValue;

float duration, cm, inches;
long tempss;
long tempsss;
SoftwareSerial espSerial(6, 5);

SoftwareSerial gsm(10, 9);
String str;
String msg;
#define MQ2pin A2

float sensorValue;

#define buzzer 2
#define POMPE 8

#define trigPin 11
#define echoPin 12
namespace pin {
const byte tds_sensor = A1;
const byte one_wire_bus = 7;
}


unsigned char temperature_icon[] = {
  0b00000001, 0b11000000,  //        ###
  0b00000011, 0b11100000,  //       #####
  0b00000111, 0b00100000,  //      ###  #
  0b00000111, 0b11100000,  //      ######
  0b00000111, 0b00100000,  //      ###  #
  0b00000111, 0b11100000,  //      ######
  0b00000111, 0b00100000,  //      ###  #
  0b00000111, 0b11100000,  //      ######
  0b00000111, 0b00100000,  //      ###  #
  0b00001111, 0b11110000,  //     ########
  0b00011111, 0b11111000,  //    ##########
  0b00011111, 0b11111000,  //    ##########
  0b00011111, 0b11111000,  //    ##########
  0b00011111, 0b11111000,  //    ##########
  0b00001111, 0b11110000,  //     ########
  0b00000111, 0b11100000,  //      ######
};

unsigned char humidity_icon[] = {
  0b00000000, 0b00000000,  //
  0b00000001, 0b10000000,  //        ##
  0b00000011, 0b11000000,  //       ####
  0b00000111, 0b11100000,  //      ######
  0b00001111, 0b11110000,  //     ########
  0b00001111, 0b11110000,  //     ########
  0b00011111, 0b11111000,  //    ##########
  0b00011111, 0b11011000,  //    ####### ##
  0b00111111, 0b10011100,  //   #######  ###
  0b00111111, 0b10011100,  //   #######  ###
  0b00111111, 0b00011100,  //   ######   ###
  0b00011110, 0b00111000,  //    ####   ###
  0b00011111, 0b11111000,  //    ##########
  0b00001111, 0b11110000,  //     ########
  0b00000011, 0b11000000,  //       ####
  0b00000000, 0b00000000,  //
};

unsigned char arrow_down_icon[] = {
  0b00001111, 0b11110000,  //     ########
  0b00011111, 0b11111000,  //    ##########
  0b00011111, 0b11111000,  //    ##########
  0b00011100, 0b00111000,  //    ###    ###
  0b00011100, 0b00111000,  //    ###    ###
  0b00011100, 0b00111000,  //    ###    ###
  0b01111100, 0b00111110,  //  #####    #####
  0b11111100, 0b00111111,  // ######    ######
  0b11111100, 0b00111111,  // ######    ######
  0b01111000, 0b00011110,  //  ####      ####
  0b00111100, 0b00111100,  //   ####    ####
  0b00011110, 0b01111000,  //    ####  ####
  0b00001111, 0b11110000,  //     ########
  0b00000111, 0b11100000,  //      ######
  0b00000011, 0b11000000,  //       ####
  0b00000001, 0b10000000,  //        ##
};

unsigned char sun_icon[] = {
  0b00000000, 0b00000000,  //
  0b00100000, 0b10000010,  //   #     #     #
  0b00010000, 0b10000100,  //    #    #    #
  0b00001000, 0b00001000,  //     #       #
  0b00000001, 0b11000000,  //        ###
  0b00000111, 0b11110000,  //      #######
  0b00000111, 0b11110000,  //      #######
  0b00001111, 0b11111000,  //     #########
  0b01101111, 0b11111011,  //  ## ######### ##
  0b00001111, 0b11111000,  //     #########
  0b00000111, 0b11110000,  //      #######
  0b00000111, 0b11110000,  //      #######
  0b00010001, 0b11000100,  //    #   ###   #
  0b00100000, 0b00000010,  //   #           #
  0b01000000, 0b10000001,  //  #      #      #
  0b00000000, 0b10000000,  //         #
};

namespace device {
float aref = 4.3;
}

namespace sensor {
float ec = 0;
float tds = 0;
float waterTemp = 0;
float ecCalibration = 1;
}

OneWire oneWire(pin::one_wire_bus);
DallasTemperature dallasTemperature(&oneWire);


void setup() {
  pinMode(SensorPin, INPUT);
  Serial.begin(115200);
  espSerial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
  display.display();
  display.clearDisplay();
  display.display();
  display.setTextSize(1);  // taille du texte
  display.setTextColor(WHITE);
  display.setCursor(0, 0);  // position du curseur colonne / ligne temperature_icon[]
  display.println("BIENVENU A NOTRE ");
  display.println(" ");
  display.println("FERME PISCICOLE");
  //display.println(" ");
  display.println("SAMAKI YA KWETU");
  display.display();
  delay(10000);
  display.clearDisplay();
  display.display();
  dallasTemperature.begin();
  pinMode(trigPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(POMPE, OUTPUT);
  pinMode(echoPin, INPUT);
  gsm.begin(9600);
  tempss = millis();
  tempsss = millis();
}

void loop() {
  envoiDeDonner();
  moniteurSerie();
  capteurPH();
  affichageoled();
  capteurTemperatureTDS();
  distanceMesure();
  capteurMQ2();
  sonnerie();

  //delay(10000);
}
