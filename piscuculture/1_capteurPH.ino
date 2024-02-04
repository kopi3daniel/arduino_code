void capteurPH(){

  for(int i=0;i<10;i++){ //Get 10 sample value from the sensor for smooth the value
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++){ //sort the analog from small to large
    for(int j=i+1;j<10;j++){
      if(buf[i]>buf[j]){
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)avgValue+=buf[i];  //take the average value of 6 center sample
    
  phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue = -5.70 * phValue + calibration_value; //convert the millivolt into pH value
  
//   //lcd.setCursor(0, 0);  
//   //lcd.print(" pH Valeur: ");
//   //lcd.print(phValue); 
//  // lcd.print("  ");
      
//  // lcd.setCursor(1, 1); 

//     if(phValue<4) { envoiesms("0972767814","eau est vrai acide.");Serial.println("eau est vraie acide.");}        
// else if(phValue>=4  && phValue<5) {envoiesms("0972767814","eau est acide.");Serial.println("eau est acide.");}
// else if(phValue>=5  && phValue<7)  {envoiesms("0972767814","eau est tend vers acide.");Serial.println("eau esttend vers acide.");}
// else if(phValue>=7  && phValue<8)  {
  
// }
// else if(phValue>=8  && phValue<10) {envoiesms("0972767814","eau est tend vers Alkaline.");Serial.println("eau est tend vers Alkaline.");}
// else if(phValue>=10 && phValue<11) {envoiesms("0972767814","eau est  Alkaline.");Serial.println("eau est Alkaline.");}
// else if(phValue>=11)               {envoiesms("0972767814","eau est vraie Alkaline.");Serial.println("eau est vraie Alkaline.");}
  
    
      
  delay(1000);
  msg =String(phValue)+String("PH    ")+String(sensor::tds)+String("TDS   ")+String(sensor::ec, 2)+String("EC  ")+String(cm)+String("litre  ")+String(sensorValue)+String("gaz   ")+String(sensor::waterTemp,2)+String("temperature  ");
  envoiesms("0972767814",msg);

}