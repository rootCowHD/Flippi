// USB / Debugging

//Modifiziert auf String S1 statt String
void serialEvent(){
  while (Serial.available()) {
    inputStringS1 += (char)Serial.read();
    if(inputStringS1.length()>=cmdLength){
      stringCompleteS1 = true;
      Serial.print("command Complete: ");
      return;
    }
  }
  
}

/*Geblockt für Verwendug mit Arduino Uno
// Interrupt für Punkte Befehle
void serialEvent1(){
  inputStringS1="";
   while (Serial1.available()) {
    inputStringS1 += (char)Serial1.read();
  }
  stringCompleteS1 = true;
}

// Interrupt für Schläger Befehle
void serialEvent2(){
  inputStringS2="";
  while (Serial2.available()) {
    inputStringS2 += (char)Serial2.read();
  }
  stringCompleteS2 = true;
}

// Interrupt für addOns
void serialEvent3(){
  inputStringS3="";
  while (Serial3.available()) {
    inputStringS3 += (char)Serial3.read();
  }
  stringCompleteS3 = true;
}

/**/
// Keine Interrupts für Software Serial
void RXTXCommand(){
  String command = inputString;
  inputStringVS = "";
  stringCompleteVS = false;
  customRXTX();

}

