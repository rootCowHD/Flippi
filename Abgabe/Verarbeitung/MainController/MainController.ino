//V0.1 zentrale Steuereinheit für Flippi
//Verarbeitung von Eingaben und Weitergabe an die Ausgabe.
/* Verwendung:
 * Verbindung des Moduls über entsprechende Schnittstellen
 * Siehe hierfür  http://hrw-fablab.de/wiki/index.php?title=Flippi#Zentrale_Steuereinheit
 */
/* Nächste Schritte:
 * Einstellung der Kommmandolänge
 * Speichern von Bestenlisten im EEPROM
 * Bereitstellung von mehr addOn Kompatibilität
 */
/* Kommandos:
 * Ausgabe:
 * "gp:" Sendet einen Punktewert
 * Eingabe:
 * "gp+:" Erhöht den Punktewert
 * "gp-:" Reduziert den Punktewert
 * "gps:" Setzt den Punktewert fest
 * "rst:" Reset des Spiels
 */
/* EEPROM:
 * Noch nicht in Verwendung
 */
#include <SoftwareSerial.h>
#include <EEPROM.h>

//Serielle Kommunikation:
//Geschwindigkeit
int usbBusSpeed = 9600;     //Serial0
int pointBusSpeed = 9600;   //Serial1
int hitterBusSpeed = 0;     //Serial2, noch nicht implementiert
int addOnBusSpeed = 9600;   //Serial3

//Eingabe Strings
String inputString = "";    //USB
String inputStringS1 = "";  //Externe Punkte
String inputStringS2 = "";  //Kommunikation mit Auslösermodul
String inputStringS3 = "";  //Für spätere Addons
String inputStringVS = "";  //Bidirektionaler SoftwareSerial

//Anzeige der Verfügbarkeit von Daten:
boolean stringComplete = false;
boolean stringCompleteS1 = false;
boolean stringCompleteS2 = false;
boolean stringCompleteS3 = false;
boolean stringCompleteVS = false;

//Virutelle Serielle Kommunikation (Nur Ausgabe)
const int vPointsOutTX = 8;
const int vPointsOutRX = 12;
const int vPointSpeed = 4800;
String inputStringVPOut = "";
SoftwareSerial vPointsOut(vPointsOutRX,vPointsOutTX);

//Aktueller Spielstand
unsigned long gamePoints = 0;

//Länge der Bestenliste
const int topListLength = 25;
int cmdLength=20;

//Struktur zum Speichern einer Bestenliste im EEPROM
//Derzeit noch nicht in Verwendung
//Die Definition der Struktur wird vor ihrer Verwendung benötigt, siehe topList.ino
typedef struct sEntry{
  char m_player[16];
  unsigned long m_points; 
} sEntry;

// Bestenliste
struct sEntry topList[topListLength];

void setup() {
  customLoadTime();  
  initBus();  
  initMain();
  customInit();
  customLoadFinish();

  Serial.println("Ready");

}

void loop() {
  ///Test für Arduino Uno als CPU
  if(stringCompleteS1)pointCommand();
  //if(stringComplete)   debugCommand();
  //if(stringCompleteS1) pointCommand();
  //Die Folgenden Teile werden in der Demo nicht verwendet
 // if(stringCompleteS2) hitterCommand();
 // if(stringCompleteS3) addOnCommand();
 // if(stringCompleteVS) RXTXCommand();
}

void initMain(){
  //Hier wird später die Bestenliste und weitere vorgefertigte Anwendungen geladen.
}

void initBus(){
  Serial.begin(pointBusSpeed);
  //Serial.begin(usbBusSpeed);
  //Serial1.begin(pointBusSpeed);
  //Serial2.begin(hitterBusSpeed); //Keine Verwendung in der Demo
  //Serial3.begin(addOnBusSpeed); //Keine Verwendung in der Demo
  vPointsOut.begin(vPointSpeed);
  initCustomBus();
  
}

