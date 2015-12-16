#include <Tone.h>

// A fun sketch to demonstrate the use of the Tone library.

// To mix the output of the signals to output to a small speaker (i.e. 8 Ohms or higher),
// simply use 1K Ohm resistors from each output pin and tie them together at the speaker.
// Don't forget to connect the other side of the speaker to ground!

// You can get more RTTTL (RingTone Text Transfer Language) songs from
// http://code.google.com/p/rogue-code/wiki/ToneLibraryDocumentation

#include <Tone.h>
Tone tone1;

#define OCTAVE_OFFSET 0

int notes[] = { 0,
NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7
};



//ALARMA
//VARS
//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 20;        

//the time when the sensor outputs a low impulse
long unsigned int lowIn;         

//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped
long unsigned int pause = 5000;  

boolean lockLow = true;
boolean takeLowTime;  

int pirPin = 7;    //the digital pin connected to the PIR sensor's output

char *zelda = "";

void setup(void)
{
  Serial.begin(9600);
  tone1.begin(3);
  
  pinMode(pirPin, INPUT);  
  digitalWrite(pirPin, LOW);
  //give the sensor some time to calibrate //Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      //Serial.print(".");
      delay(1000);
      }
    //Serial.println(" done");
    //Serial.println("SENSOR ACTIVE");
    //play_rtttl(act);
    delay(50);
  
}

#define isdigit(n) (n >= '0' && n <= '9')

void play_rtttl(char *p)
{
  // Absolutely no error checking in here

  byte default_dur = 4;
  byte default_oct = 6;
  int bpm = 63;
  int num;
  long wholenote;
  long duration;
  byte note;
  byte scale;

  // format: d=N,o=N,b=NNN:
  // find the start (skip name, etc)

  while(*p != ':') p++;    // ignore name
  p++;                     // skip ':'

  // get default duration
  if(*p == 'd')
  {
    p++; p++;              // skip "d="
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    if(num > 0) default_dur = num;
    p++;                   // skip comma
  }

  //Serial.print("ddur: "); Serial.println(default_dur, 10);

  // get default octave
  if(*p == 'o')
  {
    p++; p++;              // skip "o="
    num = *p++ - '0';
    if(num >= 3 && num <=7) default_oct = num;
    p++;                   // skip comma
  }

  //Serial.print("doct: "); Serial.println(default_oct, 10);

  // get BPM
  if(*p == 'b')
  {
    p++; p++;              // skip "b="
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    bpm = num;
    p++;                   // skip colon
  }

  //Serial.print("bpm: "); Serial.println(bpm, 10);

  // BPM usually expresses the number of quarter notes per minute
  wholenote = (60 * 1000L / bpm) * 4;  // this is the time for whole note (in milliseconds)

  //Serial.print("wn: "); Serial.println(wholenote, 10);


  // now begin note loop
  while(*p)
  {
    // first, get note duration, if available
    num = 0;
    while(isdigit(*p)) num = (num * 10) + (*p++ - '0');    
    if(num) duration = wholenote / num;
    else duration = wholenote / default_dur;  // we will need to check if we are a dotted note after

    // now get the note
    note = 0;

    switch(*p)
    {
      case 'c':
        note = 1;
        break;
      case 'd':
        note = 3;
        break;
      case 'e':
        note = 5;
        break;
      case 'f':
        note = 6;
        break;
      case 'g':
        note = 8;
        break;
      case 'a':
        note = 10;
        break;
      case 'b':
        note = 12;
        break;
      case 'p':
      default:
        note = 0;
    }
    p++;

    // now, get optional '#' sharp
    if(*p == '#') {
      note++;
      p++;
    }

    // now, get optional '.' dotted note
    if(*p == '.') {
      duration += duration/2;
      p++;
    }
  
    // now, get scale
    if(isdigit(*p)) {
      scale = *p - '0';
      p++;
    }
    else scale = default_oct;
    scale += OCTAVE_OFFSET;

    if(*p == ',') p++; // skip comma for next note (or we may be at the end)

    // now play the note

    if(note)
    {
      //Serial.print("Playing: ");
      //Serial.print(scale, 10); Serial.print(' ');
      //Serial.print(note, 10); Serial.print(" (");
      //Serial.print(notes[(scale - 4) * 12 + note], 10);
      //Serial.print(") ");
      //Serial.println(duration, 10);
      tone1.play(notes[(scale - 4) * 12 + note]);
      delay(duration);
      tone1.stop();
    }
    else
    {
      //Serial.print("Pausing: ");
      //Serial.println(duration, 10);
      delay(duration);
    }
  }
}

int song = 0;

void alarm(int state)
{  
  if(digitalRead(pirPin) == HIGH){
    //digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
    //if(lockLow){  
      //makes sure we wait for a transition to LOW before any further output is made:
      //lockLow = false;        
          
      //Serial.println("---");
      //Serial.print("motion detected at ");
      //Serial.print(millis()/1000);      
      //Serial.println(" sec"); 

      Serial.println("3");      
	  if (state == 1) { #Play a sound only if state == 1, else the alarm is silent
		  if (song == 1) {
			zelda = "Song of Storms:d=4,o=5,b=180:8d6,8f6,d7,p,8d6,8f6,d7,p,e7,8p,8f7,8e7,8f7,8e7,8c7,a6,8p,a6,d6,8f6,8g6,2a6,8p,a6,d6,8f6,8g6,2e6,8p,8d6,8f6,d7,p,8d6,8f6,d7,p,e7,8p,8f7,8e7,8f7,8e7,8c7,a6,8p,a6,d6,8f6,8g6,a6,8p,a6,1d6";
			play_rtttl(zelda);
		  }      
		  else if (song == 2) {
			zelda = "Lost Woods:d=4,o=5,b=140:8f6,8a6,b6,8f6,8a6,b6,8f6,8a6,8b6,8e7,d7,8b6,8c7,8b6,8g6,2e6,8d6,8e6,8g6,2e6,8f6,8a6,b6,8f6,8a6,b6,8f6,8a6,8b6,8e7,d7,8b6,8c7,8e7,8b6,2g6,8b6,8g6,8d6,2e6";
			play_rtttl(zelda);        
		  }
		  else if (song == 0) {
			zelda = "Gerudo Valley:d=4,o=5,b=125:16c#,16f#,16g#,8a,16p,16c#,16f#,16g#,a,8p,16d,16f#,16g#,8a,16p,16d,16f#,16g#,a,8p,16b4,16e,16f#,8g#,16p,16b4,16e,16f#,g#,8p,16f#,16g#,16f#,2f,8p,16c#,16f#,16g#,8a,16p,16c#,16f#,16g#,a,8p,16d,16f#,16g#,8a,16p,16d,16f#,16g#,a,8p,16b4,16e,16f#,8g#,16p,16b4,16e,16f#,g#,8p,16a,16b,16a,2g#";
			play_rtttl(zelda); 
		  }    
		  //Serial.print("Song ended");     
		  song++;
		  if(song > 2) song = 0;      
		  delay(50);
	  }
    }
    //takeLowTime = true;
  

  if(digitalRead(pirPin) == LOW){       
    //digitalWrite(ledPin, LOW);  //the led visualizes the sensors output pin state

   // if(takeLowTime){
     // lowIn = millis();          //save the time of the transition from high to LOW
      //takeLowTime = false;       //make sure this is only done at the start of a LOW phase
    //}
    //if the sensor is low for more than the given pause, we assume that no more motion is going to happen
    //if(!lockLow && millis() - lowIn > pause){  
      //makes sure this block of code is only executed again after a new motion sequence has been detected
     // lockLow = true;                        
      //Serial.print("motion ended at ");      //output
      //Serial.print((millis() - pause)/1000);
      //Serial.println(" sec");
      delay(50);
    
  }
}

String activada = "1";

void loop(void)
{
  if (activada == "1") alarm(1);
  if (activada == "2") alarm(2);
  if(Serial.available() > 0) {
    activada = Serial.readString();
    Serial.println(activada);    
  }  
}
