// USB / Debugging
void serialEvent(){
  inputString="";
  while (Serial.available()) {
    inputString += (char)Serial.read();
  }
  stringComplete = true;
}

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


// Keine Interrupts für Software Serial
void RXTXCommand(){
  String command = inputString;
  inputStringVS = "";
  stringCompleteVS = false;
  customRXTX();

}

