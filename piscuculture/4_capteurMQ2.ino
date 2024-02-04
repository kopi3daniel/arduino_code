void capteurMQ2(){
  sensorValue = analogRead(MQ2pin)/10; 
  if(sensorValue>50){
    // envoiesms("0972767814","le gaz etre trop dans l'eau.");
    // Serial.println("le gaz etre trop dans l'eau.");
  }

}