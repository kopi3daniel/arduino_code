
#include <MPU6050_tockn.h>
#include <Wire.h>

#include <Servo.h>


MPU6050 mpu6050(Wire);

#define pinControllerMoteurGauche 10
#define pinControllerMoteurDroit 9


Servo moteurGauche;
Servo moteurDroit;

void setup() {

  moteurGauche.attach(pinControllerMoteurGauche);
  moteurDroit.attach(pinControllerMoteurDroit);

  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void loop() {
  mpu6050.update();
  Serial.print("angleX : ");
  float anglexx = mpu6050.getAngleX();

  float vitesseRegulerMoteurDroit,vitesseRegulerMoteurGauche;

 // float valeur= vitesseRegulerMoteurDroit<anglexx<vitesseRegulerMoteurGauche;
 // Serial.print(valeur);

 vitesseRegulerMoteurDroit=map(anglexx, 0, 180, 0,2000);
 vitesseRegulerMoteurGauche=map(anglexx, -180,0, 0, 2000);


  Serial.print(anglexx);
  Serial.print("      tangleY : ");
  Serial.print(mpu6050.getAngleY());
  Serial.print("  tangleZ : ");
  Serial.print(mpu6050.getAngleZ());
   Serial.print("  moteur droite : ");
  Serial.print(vitesseRegulerMoteurDroit);
   Serial.print("  moteur gauche : ");
  Serial.println(vitesseRegulerMoteurGauche);



  moteurGauche.writeMicroseconds(vitesseRegulerMoteurDroit);
  moteurDroit.writeMicroseconds(vitesseRegulerMoteurGauche);
}
