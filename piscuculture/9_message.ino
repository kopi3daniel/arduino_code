void envoiesms(String numero , String sms) {
  gsm.println("AT");
Serial.println("AT");
  delay(200);
  gsm.println("AT+CMGF=1");
  Serial.println("AT+CMGF=1");
  delay(200);
  gsm.print("AT+CMGS=\"");
  Serial.println("AT+CMGS=\"");

  gsm.print(numero);
  Serial.println(numero);
  gsm.println("\"");
  delay(200);
  gsm.print(sms);Serial.println(sms);
  delay(1000);
  gsm.write(26);
  delay (500);
}
void messagerEnvoie(){
  
  
  // msg =String(phValue)+String("PH   ")+String(sensor::tds)+String("TDS  ")+String(sensor::ec, 2)+String("EC  ")+String(cm)+String("litre  ")+String(sensorValue)+String("gaz  ")+String(sensor::waterTemp,2)+String("temperature  ");
 // envoiesms("0972767814",msg);
  // if ((millis() - tempsss) > 2000) {
  //   tempsss = millis();
  //   envoiesms("0972767814",msg);
  // }
}