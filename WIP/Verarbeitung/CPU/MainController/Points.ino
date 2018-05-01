// Funktionen zur Kommunikation mit dem Punkte Rechner

// Selektiert einen entsprechenden Befehl
void pointCommand(){
  String command = inputStringS1;
  inputStringS1 = "";
  stringCompleteS1 = false;

  if(command.substring(0,2) == "add") addPoints(command.substring(3).toInt());
  else if(command.substring(0,2) == "sub") subPoints(command.substring(3).toInt());
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
  virtualPointSerial.print("gp");
  virtualPointSerial.println(gamePoints);
}

