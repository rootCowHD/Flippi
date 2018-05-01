//V0.1 Ausgabemodul für Flippi
//Anzeige über Display und WLAN
/* Verwendung:
 * Anschluss eines ST7735 Display
 * Verbindung des Endgerätes in das WLAN der NodeMCU
 * SSID: FLIPPI-V00STEFAN
   Passwort: FLIPPI-PASSWORD1
   IP: 192.168.4.1
 * Start der App
 */
/* Nächste Schritte:
 * Konfigurationsmöglichkeiten für das WLAN
 * Zusatzoptionen für das Display
 * Optimiertung der Ausgabegeschwindigkeiten
 * Einstellung der Kommmandolänge
 * 
 */
/* App:
 * 
 */
/* Kommandos:
 * "gp:" gibt den Punktestand an
 */
/* EEPROM:
 * Byte(s): Bedeutung:
 * 0-15     SSID
 * 16-31    Passwort
 * 32       Nicht belegt
 * 33       Länge der SSID (Maximal 16)
 * 34       Länge des Passworts (Maximal 16)
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <Adafruit_GFX.h>   
#include <Adafruit_ST7735.h> 
#include <SPI.h>

//Bildschirm
//16 bit Farbe R5 G6 B5
#define TFT_CS D2
#define TFT_RST 1
#define TFT_DC D4
#define TFT_ROTATION 1
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);


//WLAN Einstellungen
char ssid[17] = "";
char password[17] = "";
IPAddress apIP(192, 168, 4, 1);
ESP8266WebServer server ( 80 );

//Serial Einstellungen
int serialSpeed = 4800;
String inputString="";
String cmdString="";
bool stringComplete=false;
int cmdLength = 20;

//Punkte
String points="0";

void setup() {
  //Abschalten des Watchdogs
  //ESP.wdtDisable();
  EEPROM.begin(34); //Freigabe von 34 Bit im EEPROM
  Serial.begin(serialSpeed);  
  
  readWlanConfig(); //Laden der WLAN Konfiguration
  WiFi.mode(WIFI_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);

  delay(100);
  //Anzeige der Werte über den Serial Port
  //Eine Rückführung der Seriellen Kommunikation an die zentrale Steuereinheit ist nicht vorgesehen
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Passwort: ");
  Serial.println(password);
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());

  //Vorbereiten des Webservers
  server.on("/Point",handlePoints);
  server.begin();
  Serial.println("Server Config done");

  //Initierung des Displays
  initDisplay();

  Serial.flush();
  Serial.println("Config done");
}

//Gibt eine Leere Seite auf dem Server aus
void handlePoints(){
  server.send(200, "text/html", points);
}

//Voreinstellunf des Displays
void initDisplay(){
  
  tft.initR(INITR_BLACKTAB);  //Start mit einem leeren Tab
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK); //Weißer Text, schwarzer Hintergrund
  tft.fillScreen(ST7735_BLACK); //Füllt den Bildschirm Schwarz
  tft.setTextWrap(true);  //Aktiviert das vollständige Überschreiben von Buchstaben
  tft.setRotation(TFT_ROTATION); // Gibt die Rotation des Bildschirms an
  tft.setTextSize(2); //Gibt die Größe des Textes an
/**/
  Serial.println("Display Config done");
  //ToDo: Hier verwendete Werte dynmanisch angeben und regelbar machen.
}

void loop() {
  server.handleClient();
//  Serial.println("Server handeled");
  serialHandler();
 // Serial.println("Serial handeled");
  commandHandler();
  ///Serial.println("Commands handeled");
  updateDisplay();
 // Serial.println("Display handeled");
}

//Abhandeln Serieller Events
//Serialevents stehen bei ESP8266 Controllern derzeit nicht zur Verfügung
void serialHandler(){
  //Überprüfung ob Serielle Kommunikation zum Lesen zur Verfügung steht
  //Und ob noch kein String verarbeeitet wird
  if(Serial.available() && !stringComplete){
    Serial.print("+");
    while (Serial.available()) {  //Solange der eingehende Text nicht abgearbeitet ist
      inputString += (char)Serial.read(); //wird Zeichen für Zeichen an den Input String gehängt

      //Sobald der String die Länge eines Kommandos erreicht hat
      if(inputString.length()>=cmdLength){ 
        cmdString=inputString.substring(0,cmdLength); //Wird das Kommando übertragen
        Serial.print("command Complete: ");
        Serial.println(cmdString);
        //Und die Kommandoverarbeitung sowie eine neue Ausgabe werden vorbereitet
        inputString=""; 
        stringComplete=true;
        return;
      }
    }
  }
}

//Verarbeitung der Kommandos
void commandHandler(){
  if(stringComplete){
    Serial.println("handling command");
    Serial.println(cmdString);
    stringComplete=false;  
    if(cmdString.substring(0,3) == "gp:") pointCall(cmdString.substring(3));
    else customCommands();
    
  } 
}

//Speichert die Punkte ein
void pointCall(String S){
  points = S;
  Serial.print("points String: ");
  Serial.println(points);
}

//Regelt die Anzeige auf dem Display
void updateDisplay(){
  showPoints(); //Anzeige der Punkte
  customDisplay();  //Anzeige von NAchträglich eingefügten Display Befehlen
}

//Anzeige der Punkte
void showPoints(){
  tft.setCursor(5,5);
  tft.print(points);
}

//Liest die WLAN Konfiguration aus dem EEPROM
void readWlanConfig(){
  int s = EEPROM.read(32);  //Bit zur Angabe der Länge der SSID
  int p = EEPROM.read(33);  //Bit zur Angabe der Länge des Passworts
  int i = 0;
  int j = 0;
  
  while (i<s){
    ssid[i] = EEPROM.read(i); //Überschreibt die SSID mit den ersten s Stellen des EEPROMS
    i++;
  }
  while (j<p){
    password[j] = EEPROM.read(j+16); //Überschreibt das Passwort mit p Stellen aus dem EEPROM ab Stelle 16
    j++;
  }
  Serial.println("WLAN Config done");
}

//Schreibt 34 Bit einzeln in den EEPROM
//Nur verwendet um SSID und Passwort abzulegen
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
  EEPROM.commit();  //Wird benötigt um bei der NodeMCU das schreiben auf den EEPROM zu bestätigen
}

