#include<LiquidCrystal.h>
#include <EEPROM.h>
LiquidCrystal lcd(2,3,4,5,6,7);

int cont = 0;

int in1 = A0;
int in2 = A1;
int in3 = A2;
int in4 = A3;

int remotePins [] = { A0, A1, A2, A3};

int set = 0;
int stop = 0, stop1;
int mode = 0;

int buz = 13;

int timer = 0;
 
int pump = 8;
//int motor = 9;

int ir_start = 10;
int ir_fill = 11;
int ir_stop = 12;


int dist;
long duration;

int val1=0,val2=0,val3=0,val4=1;
long result=0;

void setup(){
 for (int i = 0; i < 5; i ++) {
  pinMode (remotePins [i], INPUT);
  digitalWrite(remotePins [i], HIGH);
}

pinMode(ir_fill, INPUT);
pinMode(ir_start, INPUT);
pinMode(ir_stop, INPUT);


pinMode(motor, OUTPUT);
pinMode(pump, OUTPUT);

pinMode(buz, OUTPUT);

lcd.begin(16,4);
lcd.setCursor(0,0);lcd.print("  MALIKIYA X  ");
lcd.setCursor(0,1);lcd.print("Malaxeur ya rangi");
delay(2000); 
Serial.begin(9600);
Read();
 
lcd.clear(); 
}

void loop(){

if(stop==0){
if(digitalRead (in1) == 0){
lcd.clear();
mode = mode+1; 
if(mode>4){mode=0;
Write();
Read();
lcd.setCursor(0,0);
lcd.print("  Ok enregistrement ");
delay(1000);
}
delay(300);}
  
if(digitalRead (in2) == 0){
if(mode==1){val1 = val1+1;}
if(mode==2){val2 = val2+1;}
if(mode==3){val3 = val3+1;}
if(mode==4){val4 = val4+1;}
if(val1>9){val1=0;}
if(val2>9){val2=0;}
if(val3>9){val3=0;}
if(val4>9){val4=0;}
delay(300);
}
}

if(mode==0){
if(digitalRead (in3) == 0){stop=0;}
if(digitalRead (in4) == 0){stop=1;}

lcd.setCursor(0,0);
lcd.print("malaxeur");

lcd.setCursor(0,1);
lcd.print("Fill Time =");
lcd.print(result);  
lcd.print("   ");
}else{

lcd.setCursor(0,0);
lcd.print("litre= ");
lcd.print(val4); 
lcd.print(val3);
lcd.print(val2);
lcd.print(val1);

if(mode==4) {lcd.setCursor(10,1);lcd.print("-");} 
if(mode==3) {lcd.setCursor(11,1);lcd.print("-");}
if(mode==2) {lcd.setCursor(12,1);lcd.print("-");} 
if(mode==1) {lcd.setCursor(13,1);lcd.print("-");} 
}




if(stop==1){   
if(digitalRead (ir_stop) == 1){
analogWrite(motor, 200);
if(digitalRead (ir_fill) == 0){
if(stop1==0){stop1=1;
analogWrite(motor, 0); 
delay(200);
digitalWrite(pump, HIGH);
delay(result);
digitalWrite(pump, LOW);
 
}
analogWrite(motor, 200);
}
}

if(digitalRead (ir_start) == 0){stop1=0;}

}
else{analogWrite(motor, 0);delay(300);}
}else{analogWrite(motor, 0);}

}
void Read(){
val1 = EEPROM.read(11); val2 = EEPROM.read(12); val3 = EEPROM.read(13); val4 = EEPROM.read(14);  
result = val4*1000+val3*100+val2*10+val1;  
Serial.println(result);  
}

void Write(){  
EEPROM.write(11, val1);EEPROM.write(12, val2);EEPROM.write(13, val3);EEPROM.write(14, val4);
}

