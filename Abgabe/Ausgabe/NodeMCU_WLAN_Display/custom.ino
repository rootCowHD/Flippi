//Verfügbare Informationen:
//char[17] ssid : Die SSID des zu verwendenen WLANs
//char[17] password : Das WLAN Passwort
//String Points : Ausgabe der Punkte als String


//Eigene Befehle können hier eingefügt werden.
void customCommands(){
  
}

//Eigene Anzeigen können hier eingefügt werden
//Die Höhe 0-45 wird für Punkte verwendet
void customDisplay(){
  tft.setCursor(5,50);
  tft.println(ssid);
  tft.println(password);
}

