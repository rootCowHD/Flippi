pl/**
 * Version 1:
 * Grundlagen:
 * Buttons (L/R) drücken/lösen löst Interrupts aus
 * Bei geändertem Status wird dieser Seriell über TX weiter gegeben
 * 
 * Version 1.1(toDo)
 * - Bei einkommenden Signal wird ein noRX gesendet
 *   Der Maincontroller bekommt damit die Info, nichts mehr zu senden
 * - Ein Lebenszeichen wird alle x Millisekunden gesendet
 *   Um die einwandfreie Funktion mitzuteilen
 */
int LT = 0; // Left Trigger
int RT = 1; // Right Trigger

int tx = 3; // ggf. mit Widerstand
int rx = -1;  // Kein RX verfügbar 

volatile int LTV = LOW; //LT Value
volatile int RTV = LOW; //RT Value

int oldLTV = LOW; //alter Wert von LT
int oldRTV = LOW; //alter Wert von RT

void setup() {
  Serial.begin(9600);
  pinMode(LT,INPUT);
  pinMode(RT,INPUT);
  GIMSK = 0b00100000;    // Global Interrupt Mask: Deaktiviert bis auf da PinChange Bit
  PCMSK = 0b00000011;    // PinChangeMask Deaktiviert bist auf Pin 0 und 1
  sei();                 // SetEnableInterrupts aktiviert interrpts
  
  
}

void loop() {
  // Sofern der vorherige Status (old) ungleich dem neuen Status ist:
  if( LTV != oldLTV){
    if(LTV == HIGH){
      Serial.println("leftPull"); // Wenn der neue Status HIGH (gedrückt) ist, sende leftPull
    }
    else if(LTV == LOW){
      Serial.println("leftRele"); // Ansonsten wenn der neue Status LOW (Released) ist, sende leftRele
    }
    oldLTV = LTV; // Alter Wert = neuer Wert um Kommunikation zu reduzieren
  }

  // Wie LTV
  if( RTV != oldRTV){
    if(RTV == HIGH){
      Serial.println("rightPull");
    }
    else if(RTV == LOW){
      Serial.println("rightRele");
    }
    oldRTV = RTV;
  }

  // Hier kann gegebenenfalls ein Poll eingebaut werden
}

ISR(PCINT0_vect){
  LTV=digitalRead(LT);
  RTV=digitalRead(RT);
}
