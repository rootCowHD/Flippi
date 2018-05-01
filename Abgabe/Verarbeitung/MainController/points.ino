// Funktionen zur Kommunikation mit dem Punkte Rechner

// Selektiert einen entsprechenden Befehl
void pointCommand(){
  String command = inputStringS1;
  inputStringS1 = "";
  stringCompleteS1 = false;

  Serial.print("sub3: ");
  Serial.println(command.substring(0,3));
  Serial.print("late3: ");
  Serial.println(command.substring(3));
  if(command.substring(0,4) == "gp+:") addPoints(command.substring(4).toInt());
  else if(command.substring(0,4) == "gp-:") subPoints(command.substring(4).toInt());
  else pointCommandsCustom(command);

  updateOut();
}

void addPoints(int value){
  gamePoints += value;
}

void subPoints(int value){
  gamePoints -= value;
}

void updateOut(){
  String os = "gp:";
  String p = String(gamePoints);
  while(os.length()+p.length()<cmdLength){
    os+="0";
  }
  os+=p;
  vPointsOut.println(os);
  Serial.print(os);
}

