#include "Arduino.h"
#include "capteurph.h"

#define SensorPin A0
float calibration_value = 21.34 + 0.7;
unsigned long int avgValue;
int buf[10], temp;
float phValue;

void int_capteurph() {
  pinMode(SensorPin, INPUT);
}

void capteurPH() {

  for (int i = 0; i < 10; i++) {  //Obtenez 10 valeurs d'échantillon du capteur pour lisser la valeur
    buf[i] = analogRead(SensorPin);
    delay(10);
  }
  for (int i = 0; i < 9; i++) {  //trier l'analogue du petit au grand
    for (int j = i + 1; j < 10; j++) {
      if (buf[i] > buf[j]) {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
  avgValue = 0;
  for (int i = 2; i < 8; i++) avgValue += buf[i];  //prendre la valeur moyenne de 6 échantillons centraux

  phValue = (float)avgValue * 5.0 / 1024 / 6;     //convertir l'analogique en millivolt
  phValue = -5.70 * phValue + calibration_value;  //convertir le millivolt en valeur de pH
}