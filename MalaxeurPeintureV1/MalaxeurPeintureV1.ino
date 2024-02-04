#include <Keypad.h>
const int ROW_NUM = 4;
const int COLUMN_NUM = 4;
#include <LiquidCrystal.h>
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
 
char keys[ROW_NUM][COLUMN_NUM] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
 
byte pin_rows[ROW_NUM] = { 8, 9, 10, 11 };
byte pin_column[COLUMN_NUM] = { 4, 5, 6, 7 };
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);
 

String code = "";

long k=10000;
 

const int relais_moteur = 3;
 
void setup() {

  pinMode(relais_moteur, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("---MALIKAYA _ X");
  lcd.setCursor(0, 1);
  lcd.print("CHARGEMENT");

  for (int i = 0; i < 7; i++) {
    lcd.setCursor(10 + i, 1);
    lcd.print(".");
    delay(500);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Malaxeur");
  delay(2000);
  lcd.clear();
  Serial.begin(9600);
}
 
void loop() {
  char key = keypad.getKey();
 
  if (key) {
    code += key;
    lcd.setCursor(0, 1);
    lcd.print(code);
    delay(100);
  }
 
  if (key == 'D') {
    if (code.toInt() <= 1500) {
      volume = code.toInt();
      digitalWrite(relais_moteur, HIGH);
      temps=volume*K;
      delay(temps);
      digitalWrite(relais_moteur, LOW);
      delay(200);
      
    } else {
      lcd.clear();
 
      lcd.setCursor(0, 0);
      lcd.print("l:");
    }
    code = "";
  }
  
  // for(;;){
  //   digitalWrite(12,HIGH);
  //   delay(100);
  //   digitalWrite(12,LOW);
  //   delay(100);
  // }
 
}