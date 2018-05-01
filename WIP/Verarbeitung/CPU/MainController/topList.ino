
boolean saveTopList(int count){
  //Sofern die Liste nicht zu lang ist
  if (eepromOOB(count)){
    return false;
  }
  
  eepromClear(); //lösche den EEPROM
  
  for (int i=0;i<count;i++){
    if(!saveSEntry(i)){
      return false;
    }
   }
  return true;
}

//Speichert einen einzenen Eintrag in den EEPROM
boolean saveSEntry(int pos){
  if (eepromOOB(pos)){
    return false;
  }
   EEPROM.put(pos*sizeof(sEntry),topList[pos]); //und schreibe Element für Elemnt in den Speicher
   return true;
}

//Lädt die vollständige Liste
boolean loadTopList(int count){
  if (eepromOOB(count)){
    return false;
  }

  for(int i=0;i<count;i++)
  if(!loadSEntry(i)){
    return false;
  }
  return true;
}
//Sendet die Top Liste an den Ausgabe Controller
void sendTopList(){
  String tmp ="";
  tmp+="beginTopList:";
  tmp+=topListLength;
  tmp+=";";
  for(int i=0; i<topListLength;i++){
    tmp+=i;
    tmp+=":";
    tmp+=topList[i].m_player;
    tmp+=":";
    tmp+=topList[i].m_points;
    tmp+=";";
  }
  tmp+="endTopList;";
  virtualPointSerial.println(tmp);
  
}

//Lädt einen einzelnen Eintrag
boolean loadSEntry(int pos){
  if (eepromOOB(pos)){
    return false;
  }
  struct sEntry e;
  EEPROM.get(pos*sizeof(sEntry), e);
  topList[pos].m_points = e.m_points;
  for (int i=0;i<16;i++){
    topList[pos].m_player[i] = e.m_player[i];
  }
  return true;
}

//Löscht den EEPROM vollständig
void eepromClear(){
  for(int i=0; i<EEPROM.length(); i++){
    EEPROM.write(i,0);
  }
  
}

//Überprüft ob der EEPROM genug Speicher hat
boolean eepromOOB(int c){
  if(sizeof(sEntry)*c>EEPROM.length()){
    return true;
  }
  else false;
}

