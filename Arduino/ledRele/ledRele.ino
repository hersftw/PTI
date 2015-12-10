#include <sha256.h>

//#define BTN 7
#define LED 5
#define RELE 3


unsigned long time;
int sensorReading; //analog pin reading
int state = 0;
int ledState = 0;
int releState = 1;

uint8_t *hash;

unsigned long previous = 0;        // will store last time LED was updated
const long interval = 1000;        // interval

void extLed()
{
  time = millis();
  if (time - previous >= interval) {
      previous = time;
      sensorReading = analogRead(0);  //get analog reading   
      //Serial.println(sensorReading);
      if(ledState == 0 && sensorReading < 700) ledState = HIGH;
      else if(ledState == 1 && sensorReading > 800) ledState = LOW; 
  } 
}

 
 void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT); //LED OUTPUTs 
  pinMode(RELE, OUTPUT); //LED OUTPUTs
  }
  

 
void loop() {  
  
  if(Serial.available() > 0) {
    String st = Serial.readString();

    Sha256.init();
    Sha256.print(st);
    hash = Sha256.result();
    //Serial.write((char*)hash);
    Serial.write(hash,32);
    //for(int i = 0; i < 256; i++)
     // Serial.print((byte)(hash[i]));
    
    
    
    String req = Serial.readString();
    //String req = "0";
    
    if(req == "0") {
      ledState = LOW;
      state = 0;
    }
    else if(req == "1") {
      ledState = HIGH;
      state = 1;
    }
    else if(req == "2") state = 2;    
    Serial.print(req);
  //String caca = String(hash);  
    //Serial.println(String(hash));
  }

  if(state == 2) extLed();
  digitalWrite(LED, ledState);  
  releState = abs(ledState - 1);
  digitalWrite(RELE, releState); 
  
}
 
 /*

String getValue(String data, int index)
{
  char separator = ':';
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

*/



