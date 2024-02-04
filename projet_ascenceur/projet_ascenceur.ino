
#define in1 34
#define in2 35
#define in3 36
#define in4 37


#define tps0 10000


// les bouton appel
char b1;
char b2;
char b3;


//les bouton de destination

char t1;
char t2;
char t3;

//capteur de position monte

char obs1 =7;
char obs2 =8;
char obs3 =9;



//capteur de position decente

char obs4 = 40;
char obs5 = 41;
char obs6 = 42;


//initialisation de capteur

char c1;
char c2 = HIGH;
char c3;

char c4=HIGH;
char c5=HIGH;
char c6=HIGH;


// DECODEUR

char A=22;
char B=23;
char C=24;
char D=25;

// BUZZER

char buzz =31;

int note = 2000;
int note1 = 200;
int tps =2000;
int tps1= 1000;

// declaration  de led

int ledR =44 ;
int ledV =45;

char obs ; // permet de donner la position du capteur
char p_act; // variable position actuelle






void setup() {

    Serial.begin(9600);

//CAPTEUR
    pinMode(obs1, INPUT);

    pinMode(obs1, INPUT);
    pinMode(obs2, INPUT);
    pinMode(obs4, INPUT);
    pinMode(obs3, INPUT);
    pinMode(obs5, INPUT);
    pinMode(obs6, INPUT);

//BOUTON

      pinMode(2, INPUT);
      pinMode(3, INPUT);
      pinMode(4, INPUT);
      pinMode(5, INPUT);
      pinMode(6, INPUT);
      pinMode(7, INPUT);


      //ACTIVATION DU DECODEUR


      pinMode(A, OUTPUT);
      pinMode(B, OUTPUT);
      pinMode(C, OUTPUT);
      pinMode(D, OUTPUT);

      // Intialisation du led et buzzer

      pinMode(buzz, OUTPUT);
      pinMode(ledR, OUTPUT);
      pinMode(ledV, OUTPUT);

      p_act=obs;







}


char position(char a, char b, char c ,char d){
  digitalWrite(A, a);
  digitalWrite(B, b);
  digitalWrite(C, c);
  digitalWrite(D, d);
}
// sens 1
void rotation1(){
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
  delayMicroseconds(tps0);

  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
  delayMicroseconds(tps0);

  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  delayMicroseconds(tps0);

  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  delayMicroseconds(tps0);


}

// sens 2

void rotation2(){
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  delayMicroseconds(tps0);

  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
  delayMicroseconds(tps0);

  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  delayMicroseconds(tps0);

  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  delayMicroseconds(tps0);


}
void loop() {
  
//---- lecteur de capteur


c1=digitalRead(obs1);
c2=digitalRead(obs2);    // nivea haut
c3=digitalRead(obs3);

c4=digitalRead(obs4);
c5=digitalRead(obs5);
c6=digitalRead(obs6);

if(c1==1){
  obs=1;
  position(1, 0, 0, 0);
}
if((c2==2)||(c5==2)){
  obs =2;
  position(0, 1, 0, 0);

}

if(c3==3){
  position(1, 1, 0, 0);
}
 b1=digitalRead(2);
 b2=digitalRead(3);
 b3=digitalRead(4);

 t1=digitalRead(26);
 t2= digitalRead(27);
 t3= digitalRead(28);



 if ((t1==1)||(b1==1)) {
 fonction(1);
 }

  if ((t1==2)||(b1==2)) {
 fonction(2);
 }

  if ((t1==3)||(b1==3)) {
 fonction(3);
 }

 if(Serial.available()>0){
  char data =Serial.read();

  if(data == '1')fonction(1);
  if(data == '2')fonction(2);
  if(data == '3')fonction(3);


 }



}


int fonction(int donner){
  if((p_act!=donner)){
    if(donner>p_act){
      switch (donner) {
      case 1:
      while (!digitalRead(obs1)) {
        rotation1();
        digitalWrite(ledR,1 );
           
      }
    position(1, 0, 0, 0);
    digitalWrite(ledR,0);
    delay(tps);
    tone(buzz,note);
    delay(tps1);
    noTone(buzz);

    break;

    case 2:
      while (!digitalRead(obs2)) {
        rotation1();
        digitalWrite(ledR,1 );
           
      }
    position(1, 0, 0, 0);
    digitalWrite(ledR,0);
    delay(tps);
    tone(buzz,note);
    delay(tps1);
    noTone(buzz);

    break;

    case 3:
      while (!digitalRead(obs3)) {
        rotation1();
        digitalWrite(ledR,1 );
           
      }
    position(1, 0, 0, 0);
    digitalWrite(ledR,0);
    delay(tps);
    tone(buzz,note);
    delay(tps1);
    noTone(buzz);
    break;

    default:

    break;


      }
    }

    else{

      switch (donner) {
      case 1:
      while (!digitalRead(obs1)) {
        rotation2();
        digitalWrite(ledR,1 );
           
      }
    position(1, 0, 0, 0);
    digitalWrite(ledR,0);
    delay(tps);
    tone(buzz,note);
    delay(tps1);
    noTone(buzz);

    break;

    case 2:
      while (!digitalRead(obs2)) {
        rotation2();
        digitalWrite(ledR,1 );
           
      }
    position(1, 0, 0, 0);
    digitalWrite(ledR,0);
    delay(tps);
    tone(buzz,note);
    delay(tps1);
    noTone(buzz);

    break;

    case 3:
      while (!digitalRead(obs3)) {
        rotation2();
        digitalWrite(ledR,1 );
           
      }
    position(1, 0, 0, 0);
    digitalWrite(ledR,0);
    delay(tps);
    tone(buzz,note);
    delay(tps1);
    noTone(buzz);
    break;

    default:

    break;


      }


    
  }

  }

  
}