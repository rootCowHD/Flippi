
//Pins zur Verwendung um Punkte zu berechnen
const int p1 = 4;
const int p2 = 5;
const int p4 = 6;
const int p8 = 7;
const int p16 = 8;
const int p32 = 9;
const int p64 = 10;
const int p128 = 11;
const int p256 = 12;
const int p512 = 13;

//Serielle Einstellungen
int cmdLength = 20;
int serialSpeed = 9600;

unsigned long points = 0;

//Interrupt Handling
bool added = false;
bool I2C = false;

void setup() {
  Serial.begin(serialSpeed);
  //Serial.println("Start init");
  for(int i = 4; i<14; i++){
    pinMode(i,INPUT);
  //  Serial.println(i);
  }
  attachInterrupt(digitalPinToInterrupt(2),pointInterrupt,RISING);
  //attachInterrupt(1,RISING,I2CInterrupt);

  initI2C();
 // Serial.println("config done");
}

//Gibt an das auf I2C reagiert werden muss
void I2CInterrupt(){
  I2C = true;
}

//gibt an wieviele Punkte übergeben werden müssen
void pointInterrupt(){
  if(!added){
    if(digitalRead(p1) == HIGH) points+=1;
    if(digitalRead(p2) == HIGH) points+=2;
    if(digitalRead(p4) == HIGH) points+=4;
    if(digitalRead(p8) == HIGH) points+=8;
    if(digitalRead(p16) == HIGH) points+=16;
    if(digitalRead(p32) == HIGH) points+=32;
    if(digitalRead(p64) == HIGH) points+=64;
    if(digitalRead(p128) == HIGH) points+=128;
    if(digitalRead(p256) == HIGH) points+=256;
    if(digitalRead(p512) == HIGH) points+=512;/**/
    added=true;
  }
}

//Initalisierung von I2C Geräten (derzeit keins)
void initI2C(){
  //ToDo: Programmierung von I2C 
  initCustomI2C();
}

void loop() {
  handlePoints();
  handleI2C();
}

//Abhandlung von direkten Punkten
void handlePoints(){
  if(added){
   // Serial.println("handle Points");
    String os = "gp+:";
    String p = String(points);
    while(os.length()+p.length()<cmdLength){
      os+="0";
    }
    os+=p;
    Serial.println(os);
    points=0;
    delay(25);
    added=false;
  }
}

//Abhandlung von I2C
void handleI2C(){
  if(I2C){
    handleCustomI2C();
    I2C = false;
  }
}

