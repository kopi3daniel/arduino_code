void envoiDeDonner(){
  str =String(phValue)+String("   ")+String(sensor::tds)+String("   ")+String(sensor::ec, 2)+String("   ")+String(cm)+String("   ")+String(sensorValue)+String("   ")+String(sensor::waterTemp,2)+String("   ");
  espSerial.print(str);

} 