void sonnerie(){
  if(cm>17){
    digitalWrite(buzzer,HIGH);
    digitalWrite(POMPE,HIGH);
    
   }
  else {
  digitalWrite(buzzer,LOW);
  digitalWrite(POMPE,LOW);

  }



}