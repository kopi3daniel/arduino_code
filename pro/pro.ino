
#define relais1 3
#define relais2 4



void setup() {
  pinMode(relais1,OUTPUT);
  pinMode(relais2,OUTPUT);

}

void loop() {
  digitalWrite(relais1,LOW);
  delay(1000);
  digitalWrite(relais1,HIGH);
  digitalWrite(relais2,HIGH);
  delay(3000);
  digitalWrite(relais1,LOW);
  delay(1000);
  digitalWrite(relais1,HIGH);
  digitalWrite(relais2,LOW);
  delay(3000);
  
}
