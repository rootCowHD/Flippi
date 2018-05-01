#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

typedef struct sEntry{
  char m_player[16];
  unsigned long m_points; 
} sEntry;

//SSID und PW des zu erstellenden WLANs
//Für Massenproduktion muss diese Einzigartig sein
//Aufbau: "Flippi" + Eine Abfolge von 9 Buchstaben/Zahlem
//Länge 16 chars
char ssid[17] = "";
  
//Maximale Länge 16 chars
//Zur MAssenproduktion muss das Passwort zufällig sein
char password[17] = "";


ESP8266WebServer server ( 80 );

//Punkte Übertragung
int serialSpeed = 115200;
String inputString="";
const int topListLength = 25; 
bool stringComplete = false;
bool EEERROR = false;
unsigned long points = 0;


struct sEntry topList[topListLength];

void setup() {
  EEPROM.begin(34);
  Serial.begin(serialSpeed);
  //FLIPPI-PASSWORD1
  /**/

  //ToDo: 
  //Länge Anpassbar machen
  //Passwort SSID Änderbar machen
  
  int s = EEPROM.read(32);
  int p = EEPROM.read(33);

  int i = 0;
  int j = 0;
  while (i<s){
    ssid[i] = EEPROM.read(i);
    i++;
  }
  while (j<p){
    password[j] = EEPROM.read(j+16);
    j++;
  }

  WiFi.softAP(ssid, password);
  delay(100);
  
  Serial.println(WiFi.softAPIP());
  Serial.println(password);
  Serial.println("");

  server.on("/List",handleList);
  server.on("/Point",handlePoints);
  server.begin();
  
  
  

}

void loop() {
  if(!EEERROR){
    server.handleClient();
    if(Serial.available()){
      server.stop();
      inputString="";
      while (Serial.available()) {
        inputString += (char)Serial.read();
      }
      server.begin();
      serialHandler();
    }
  }
}


void handleList(){
  server.send(200, "text/html", "Ladefehler");
}

void handlePoints(){
  server.send(200, "text/html", String(points));
}

void serialHandler(){
  Serial.println(inputString);
  if(inputString.substring(0,12) == "beginTopList:") topListCall(inputString.substring(13));
  else if (inputString.substring(0,1) == "gp") pointCall(inputString.substring(2));
  stringComplete=false;
}

void pointCall(String S){
  points = S.toInt();
  Serial.println(points);
}

void topListCall(String S){
  int x = S.substring(0,S.indexOf(";")-1).toInt();
  if(x>topListLength){
    EEERROR = true;
    return;
  }
  String pl="", po="";
  for (int i=0;i<x;i++){
    if(i == S.substring(0,S.indexOf(";")-1).toInt()){
      S = S.substring(0,S.indexOf(";")+1);
      pl = S.substring(0,S.indexOf(";")-1);
      S = S.substring(0,S.indexOf(";")+1);
      po = S.substring(0,S.indexOf(";")-1);

    //ToDo: Einfügen der Daten in die Liste
    }
  }
}



//Schreibt 34 Byte in den EEPROM
//16 Maximal für SSID
//16 Maximal für PW
//2 für Länge von SSID und PW
void B34(){
  EEPROM.write(0,'F');
  EEPROM.write(1,'L');
  EEPROM.write(2,'I');
  EEPROM.write(3,'P');
  EEPROM.write(4,'P');
  EEPROM.write(5,'I');
  EEPROM.write(6,'-');
  EEPROM.write(7,'V');
  EEPROM.write(8,'0');
  EEPROM.write(9,'0');
  EEPROM.write(10,'S');
  EEPROM.write(11,'T');
  EEPROM.write(12,'E');
  EEPROM.write(13,'F');
  EEPROM.write(14,'A');
  EEPROM.write(15,'N');
  
  EEPROM.write(16,'F');
  EEPROM.write(17,'L');
  EEPROM.write(18,'I');
  EEPROM.write(19,'P');
  EEPROM.write(20,'P');
  EEPROM.write(21,'I');
  EEPROM.write(22,'-');
  EEPROM.write(23,'P');
  EEPROM.write(24,'A');
  EEPROM.write(25,'S');
  EEPROM.write(26,'S');
  EEPROM.write(27,'W');
  EEPROM.write(28,'O');
  EEPROM.write(29,'R');
  EEPROM.write(30,'D');
  EEPROM.write(31,'1');

  EEPROM.write(32,16);
  EEPROM.write(33,16);
  EEPROM.commit();
}

