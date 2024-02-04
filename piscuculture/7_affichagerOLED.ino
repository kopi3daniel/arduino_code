void affichageoled(){
  display.display();
 //  display.setTextSize(1.8,1.8);  // taille du texte
  display.setTextColor(WHITE);
  display.println(" ");
  display.setCursor(0,0);
  display.print("Temp:");
  display.print(sensor::waterTemp, 2);
  display.print("'C");
  display.print("  ");
  display.display();
  display.display();
  display.println(" "); 
  display.print("TDS :");
  display.print(sensor::tds);
  display.display();
  display.display();
  display.print(" ");
  display.display();
  display.display();
  display.display();
  //
  display.display();
  display.print("EC: ");
  display.print(sensor::ec, 2);
  display.display();
  display.display();
  display.display();
  display.print("  Gaz:");
  display.print(sensorValue );
  display.display();
  display.display();
  display.display();
  display.display();
  //display.println(" ");
  display.display();
  display.print("eau:");
  display.print(cm);
  display.display();
  display.display();
  display.display();
  display.display();
  display.print(" ");
  display.display();
  display.print("  pH");
  display.print(phValue);
  display.display();
  display.display();
  if ((millis() - tempss) > 2000) {
    tempss = millis();
    display.display();
    display.clearDisplay();
  }
}