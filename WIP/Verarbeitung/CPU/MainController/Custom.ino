// Hier angegebene Befehle erweitern den Befehlssatz eines Controllers
// Der Controller muss die Befehle senden können

// Eigene Befehle zur Initialisierung
// Lade LEDs werden in customLoadTime und customLoadFinish eingestellt
void customInit(){
  
}
/**
 * Beispiel
 void hitCommands(String cmd){
   if( cmd == "myCMD") myFunction();
   else if ( cmd == "myOtherCMD") myOtherFunction();
 */

void usbCommandsCustom(String cmd){
  
}


//Befehele des Schlägers
void hitCommandsCustom(String cmd){
  
}


//Befehle der Punkte Ausgabe
void pointCommandsCustom (String cmd){
  
}

//Befehle für AddOns
void addOnCommandsCustom (String cmd){
  
}

// Befhele die beim boot ausgeführt werden sollen
// Auch Lichter können hier eingestellt werden
void customLoadTime(){
  
}

// Befehle die nach dem fertig laden ausgeführt werden sollen
// z.B. Deaktivieren der startUp LED
void customLoadFinish(){
  
}

void customRXTX(){
  
}

