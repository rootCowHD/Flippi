/*
  GGF Wechsel auf PWM Schläger, da Attiny kein RX beherrscht
*/

#include <SoftwareSerial.h>
#include <EEPROM.h>

// Variabelen abhängig vom Aufbau:
const int topListLength = 25;   // Länge der TopList
const int linePointPinTX = 0;   // Pin zum Senden von Daten an die Punkteausgabe
const int linePointPinRX = 0;   // Pin zum Empfangen von Daten der Punkteausgabe (nur zur Definition)
const int lineHitterPinTX = 0;  // Pin zum Senden von Daten an die Hardware Schläger
const int lineHitterPinRX = 0;  // Pin zum Empfangen von Daten der Hardware Schläger (nur zur Definition)
const int lineSpringPinTX = 0;  // Pin zum Senden von Daten an eine elektronische Feder, sofern diese verwendet wird
const int lineSpringPinRX = 0;  // Pin zum Empfangen von Daten der elektronischen Feder (nur zur Definition)
const int lineLightPinTX = 0;   // Pin zum Senden von Daten an die Beleuchtung, sofern diese verwendet wird
const int lineLightPinRX = 0;   // Pin zum Empfangen von Daten der Beleuchtung (nur zur Definition)
const int lineRXTXPinTX = 0;    // Pin zum Senden von Daten am virtuellen RX/TX Pin
const int lineRXTXPinRX = 0;    // Pin zum Empfangen von Daten am virtuellen RX/TX Pin

// Schreibgeschwindigkeiten
int virtualPointSerialBaud = 4800;
int virtualHitterSerialBaud = 4800;
int virtualSpringSerialBaud = 4800;
int virtualLightSerialBaud = 4800;
int virtualRXTXSerialBaud = 4800;

int usbBusSpeed = 9600;
int pointBusSpeed = 9600;
int hitterBusSpeed = 9600;
int addOnBusSpeed = 9600;

// Kontrollvariabelen
// Serielle Strings:
String inputString = "";    //USB
String inputStringS1 = "";  //Externe Punkte
String inputStringS2 = "";  //Kommunikation mit Auslösermodul
String inputStringS3 = "";  //Für spätere Addons
String inputStringVS = "";  //Bidirektionaler SoftwareSerial

// Anzeige der Verfügbarkeit von Daten:
boolean stringComplete = false;
boolean stringCompleteS1 = false;
boolean stringCompleteS2 = false;
boolean stringCompleteS3 = false;
boolean stringCompleteVS = false;

// Punkte
unsigned long gamePoints = 0; // Siehe topList.ino

//Die Definition der Struktur wird vor ihrer Verwendung benötigt, siehe topList.ino
typedef struct sEntry{
  char m_player[16];
  unsigned long m_points; 
} sEntry;

// Bestenliste
struct sEntry topList[topListLength];

// Software Serial (nur zum Senden)
// Empfang ist nur theoretisch möglich, kein Übertragen von Systemkritischen Informationen
SoftwareSerial virtualPointSerial  (linePointPinRX,linePointPinTX);
SoftwareSerial virtualHitterSerial (lineHitterPinRX,lineHitterPinTX);
SoftwareSerial virtualSpringSerial (lineSpringPinRX, lineSpringPinTX);
SoftwareSerial virtualLightSerial  (lineLightPinRX, lineLightPinTX);
SoftwareSerial virtualRXTXSerial   (lineRXTXPinRX, lineRXTXPinTX); 

void setup() {
  customLoadTime();   // Läd
  initBus();  
  initMain();
  customInit();
  customLoadFinish();
}

void loop() {
  if(stringComplete)   debugCommand();
  if(stringCompleteS1) pointCommand();
  if(stringCompleteS2) hitterCommand();
  if(stringCompleteS3) addOnCommand();
  if(stringCompleteVS) RXTXCommand();
}


// Lädt die verschiedenen Hardware und Software Serials mit ihren entsprechenden Baud Rates
void initBus(){
  Serial.begin(usbBusSpeed);
  Serial1.begin(pointBusSpeed);
  Serial2.begin(hitterBusSpeed);
  Serial3.begin(addOnBusSpeed);
  virtualPointSerial.begin(virtualPointSerialBaud);
  virtualHitterSerial.begin(virtualHitterSerialBaud);
  virtualSpringSerial.begin(virtualSpringSerialBaud);
  virtualLightSerial.begin(virtualLightSerialBaud);
  virtualRXTXSerial.begin(virtualRXTXSerialBaud);
}

// Lädt alle Wichtigen Funktionen
void initMain(){
  loadTopList(topListLength);
  sendTopList();
}



