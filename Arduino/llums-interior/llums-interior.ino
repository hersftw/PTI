#include <NewPing.h>

#define TRIG1  3
#define ECHO1  4
#define TRIG2  9
#define ECHO2  8

#define LED1 12
#define LED2 11
#define LED3 7
#define LED4 6
#define RELE 2

#define MAX_DISTANCE1 200
#define MAX_DISTANCE2 200

NewPing sonar1(TRIG1, ECHO1, MAX_DISTANCE1);
NewPing sonar2(TRIG2, ECHO2, MAX_DISTANCE2);

long cm1, cm2;                                     // Distancies
int count = 0, last = 0;         // Num people, Last sonar
unsigned long lasttime = 0, time, previous = 0;    // Lasttime count, previous interval
const long interval = 200;    // Interval sonar (milliseconds)

boolean change;
 
void setup() {
  Serial.begin(9600);  
 
  pinMode(LED1, OUTPUT);           // LED OUTPUT 
  pinMode(LED2, OUTPUT);           // LED OUTPUT 
  pinMode(LED3, OUTPUT);           // LED OUTPUT 
  pinMode(LED4, OUTPUT);           // LED OUTPUT 
  pinMode(RELE, OUTPUT);           // LED OUTPUT 
  
  pinMode(TRIG1, OUTPUT);         // ping sensor trigger OUTPUT
  pinMode(ECHO1, INPUT);          // ping sensor echo INPUT
  pinMode(TRIG2, OUTPUT);         // ping sensor2 trigger OUTPUT
  pinMode(ECHO2, INPUT);          // ping sensor2 echo INPUT 
  digitalWrite(RELE, HIGH);
}
 
void loop() { 
  
  time = millis();  
  if ((time -lasttime) >= 2000) last = 0;  
   
  //if (time - previous >= interval) 
  //{
    //previous = time;  
    delay(50);
    
    /*pinMode(TRIG1, OUTPUT);
    digitalWrite(TRIG1, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG1, HIGH);
    delayMicroseconds(5);
    digitalWrite(TRIG1, LOW);    
    pinMode(ECHO1,INPUT);*/
    
    
    
    
    cm1 = sonar1.ping_cm();
    pinMode(ECHO1,OUTPUT);
    digitalWrite(ECHO1,LOW);
    pinMode(ECHO1,INPUT);
    
    //delay (50);
    
    
    /*pinMode(TRIG2, OUTPUT);
    digitalWrite(TRIG2, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG2, HIGH);
    delayMicroseconds(5);
    digitalWrite(TRIG2, LOW);    
    pinMode(ECHO2,INPUT);*/
    
    
    cm2 = sonar2.ping_cm();
    pinMode(ECHO2,OUTPUT);
    digitalWrite(ECHO2,LOW);
    pinMode(ECHO2,INPUT);
    
    //delay (50);
    Serial.print("1: ");    Serial.println(cm1);    
    Serial.print("2: ");    Serial.println(cm2);
    
    change = 0;
          
   if(cm1 < 60 && cm1 > 0 && (cm2 > 60 || cm2 == 0))
   {
     lasttime = millis();
     if(last == 0) last = 1;
     else if(last == 2)
     {        
       count--;
       if(count < 0) count = 0;  
       last = 0; 
       change = 1;
       //delay(200);      
     }    
   } 
    
   else if(cm2 < 60 && cm2 !=0 && (cm1 > 60 || cm1 == 0))
   {      
     lasttime = millis();
     if(last == 0) last = 2;
     else if(last == 1)
     {          
       count++;
       last = 0;  
       change = 1;
       //delay(200);     
     }  
   }    
 // }
  
  digitalWrite(LED1, count%2);          //01 01 01
  digitalWrite(LED2, (count/2)%2);      //0011 0011
  digitalWrite(LED3, (count/4)%2);      //00001111
  digitalWrite(LED4, (count/8)%2);      //0000000011111111
  
  if(change) delay(200);
  if(count > 0) digitalWrite(RELE, LOW);
  else digitalWrite(RELE, HIGH);
  
  
  //digitalWrite(LED, ledState);
}
    

