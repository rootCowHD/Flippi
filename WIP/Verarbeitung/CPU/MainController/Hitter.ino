/* 
 * Schläger Befehle
 * initHitBus: initialisiert die Hitter Befehle
 * hitSwitchCommand: Wechselt zwischen den Schläger Befehlen
 * hitLeft: Löst den linken Schläger aus
 * hitRight: Löst den rechten Schläger aus
 * relLeft: Setzt den linken Schläger zurück
 * relRight: Setzt den rechten Schläger zurück
 * hitCommands: Leerer Befehl für eigene Funktionen
 */
void hitterCommand(){
  String command = inputStringS2;
  inputStringS2 = "";
  stringCompleteS2 = false;

  if(command == "leftPull") hitLeft();
  else if( command == "rightPull") hitRight();
  else if( command == "leftRele") relLeft();
  else if( command == "rightRele") relRight();
  else hitCommandsCustom(command);
  
}

void hitLeft(){
  virtualHitterSerial.println("leftPull");
}

void hitRight(){
  virtualHitterSerial.println("rightPull");
}

void relLeft(){
  virtualHitterSerial.println("leftRele");
}

void relRight(){
  virtualHitterSerial.println("rightRele");
}
