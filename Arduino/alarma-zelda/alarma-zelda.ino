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


//char *song = "The Simpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6";
//char *song = "Indiana:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6";
//char *song = "TakeOnMe:d=4,o=4,b=160:8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5,8f#5,8e5,8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5";
//char *song = "Entertainer:d=4,o=5,b=140:8d,8d#,8e,c6,8e,c6,8e,2c.6,8c6,8d6,8d#6,8e6,8c6,8d6,e6,8b,d6,2c6,p,8d,8d#,8e,c6,8e,c6,8e,2c.6,8p,8a,8g,8f#,8a,8c6,e6,8d6,8c6,8a,2d6";
//char *song = "Muppets:d=4,o=5,b=250:c6,c6,a,b,8a,b,g,p,c6,c6,a,8b,8a,8p,g.,p,e,e,g,f,8e,f,8c6,8c,8d,e,8e,8e,8p,8e,g,2p,c6,c6,a,b,8a,b,g,p,c6,c6,a,8b,a,g.,p,e,e,g,f,8e,f,8c6,8c,8d,e,8e,d,8d,c";
//char *song = "Xfiles:d=4,o=5,b=125:e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,g6,f#6,e6,d6,e6,2b.,1p,g6,f#6,e6,d6,f#6,2b.,1p,e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,e6,2b.";
//char *song = "Looney:d=4,o=5,b=140:32p,c6,8f6,8e6,8d6,8c6,a.,8c6,8f6,8e6,8d6,8d#6,e.6,8e6,8e6,8c6,8d6,8c6,8e6,8c6,8d6,8a,8c6,8g,8a#,8a,8f";
//char *song = "20thCenFox:d=16,o=5,b=140:b,8p,b,b,2b,p,c6,32p,b,32p,c6,32p,b,32p,c6,32p,b,8p,b,b,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,g#,32p,a,32p,b,8p,b,b,2b,4p,8e,8g#,8b,1c#6,8f#,8a,8c#6,1e6,8a,8c#6,8e6,1e6,8b,8g#,8a,2b";
//char *song = "Bond:d=4,o=5,b=80:32p,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d#6,16d#6,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d6,16c#6,16c#7,c.7,16g#6,16f#6,g#.6";
//char *song = "MASH:d=8,o=5,b=140:4a,4g,f#,g,p,f#,p,g,p,f#,p,2e.,p,f#,e,4f#,e,f#,p,e,p,4d.,p,f#,4e,d,e,p,d,p,e,p,d,p,2c#.,p,d,c#,4d,c#,d,p,e,p,4f#,p,a,p,4b,a,b,p,a,p,b,p,2a.,4p,a,b,a,4b,a,b,p,2a.,a,4f#,a,b,p,d6,p,4e.6,d6,b,p,a,p,2b";
//char *song = "StarWars:d=4,o=5,b=45:32p,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#.6,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#6";
//char *song = "GoodBad:d=4,o=5,b=56:32p,32a#,32d#6,32a#,32d#6,8a#.,16f#.,16g#.,d#,32a#,32d#6,32a#,32d#6,8a#.,16f#.,16g#.,c#6,32a#,32d#6,32a#,32d#6,8a#.,16f#.,32f.,32d#.,c#,32a#,32d#6,32a#,32d#6,8a#.,16g#.,d#";
//char *song = "TopGun:d=4,o=4,b=31:32p,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,16f,d#,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,g#";
//char *song = "A-Team:d=8,o=5,b=125:4d#6,a#,2d#6,16p,g#,4a#,4d#.,p,16g,16a#,d#6,a#,f6,2d#6,16p,c#.6,16c6,16a#,g#.,2a#";
//char *song = "Flinstones:d=4,o=5,b=40:32p,16f6,16a#,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,d6,16f6,16a#.,16a#6,32g6,16f6,16a#.,32f6,32f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,a#,16a6,16d.6,16a#6,32a6,32a6,32g6,32f#6,32a6,8g6,16g6,16c.6,32a6,32a6,32g6,32g6,32f6,32e6,32g6,8f6,16f6,16a#.,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#6,16c7,8a#.6";
//char *song = "Jeopardy:d=4,o=6,b=125:c,f,c,f5,c,f,2c,c,f,c,f,a.,8g,8f,8e,8d,8c#,c,f,c,f5,c,f,2c,f.,8d,c,a#5,a5,g5,f5,p,d#,g#,d#,g#5,d#,g#,2d#,d#,g#,d#,g#,c.7,8a#,8g#,8g,8f,8e,d#,g#,d#,g#5,d#,g#,2d#,g#.,8f,d#,c#,c,p,a#5,p,g#.5,d#,g#";
//char *song = "Gadget:d=16,o=5,b=50:32d#,32f,32f#,32g#,a#,f#,a,f,g#,f#,32d#,32f,32f#,32g#,a#,d#6,4d6,32d#,32f,32f#,32g#,a#,f#,a,f,g#,f#,8d#";
//char *song = "Smurfs:d=32,o=5,b=200:4c#6,16p,4f#6,p,16c#6,p,8d#6,p,8b,p,4g#,16p,4c#6,p,16a#,p,8f#,p,8a#,p,4g#,4p,g#,p,a#,p,b,p,c6,p,4c#6,16p,4f#6,p,16c#6,p,8d#6,p,8b,p,4g#,16p,4c#6,p,16a#,p,8b,p,8f,p,4f#";
//char *song = "MahnaMahna:d=16,o=6,b=125:c#,c.,b5,8a#.5,8f.,4g#,a#,g.,4d#,8p,c#,c.,b5,8a#.5,8f.,g#.,8a#.,4g,8p,c#,c.,b5,8a#.5,8f.,4g#,f,g.,8d#.,f,g.,8d#.,f,8g,8d#.,f,8g,d#,8c,a#5,8d#.,8d#.,4d#,8d#.";
//char *song = "LeisureSuit:d=16,o=6,b=56:f.5,f#.5,g.5,g#5,32a#5,f5,g#.5,a#.5,32f5,g#5,32a#5,g#5,8c#.,a#5,32c#,a5,a#.5,c#.,32a5,a#5,32c#,d#,8e,c#.,f.,f.,f.,f.,f,32e,d#,8d,a#.5,e,32f,e,32f,c#,d#.,c#";
//char *song = "MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d";
//char *zelda_woods = "Lost Woods:d=4,o=5,b=140:8f6,8a6,b6,8f6,8a6,b6,8f6,8a6,8b6,8e7,d7,8b6,8c7,8b6,8g6,2e6,8d6,8e6,8g6,2e6,8f6,8a6,b6,8f6,8a6,b6,8f6,8a6,8b6,8e7,d7,8b6,8c7,8e7,8b6,2g6,8b6,8g6,8d6,2e6";
//char *zelda_gerudo = "Gerudo Valley:d=4,o=5,b=125:16c#,16f#,16g#,8a,16p,16c#,16f#,16g#,a,8p,16d,16f#,16g#,8a,16p,16d,16f#,16g#,a,8p,16b4,16e,16f#,8g#,16p,16b4,16e,16f#,g#,8p,16f#,16g#,16f#,2f,8p,16c#,16f#,16g#,8a,16p,16c#,16f#,16g#,a,8p,16d,16f#,16g#,8a,16p,16d,16f#,16g#,a,8p,16b4,16e,16f#,8g#,16p,16b4,16e,16f#,g#,8p,16a,16b,16a,2g#";
//char *zelda_storms = "Song of Storms:d=4,o=5,b=180:8d6,8f6,d7,p,8d6,8f6,d7,p,e7,8p,8f7,8e7,8f7,8e7,8c7,a6,8p,a6,d6,8f6,8g6,2a6,8p,a6,d6,8f6,8g6,2e6,8p,8d6,8f6,d7,p,8d6,8f6,d7,p,e7,8p,8f7,8e7,8f7,8e7,8c7,a6,8p,a6,d6,8f6,8g6,a6,8p,a6,1d6";
//char *zelda_lullaby = "Ocarina:d=4,o=5,b=100:b,16p,8d6,32p,a,16p,16g,32p,16a,32p,b,16p,8d6,32p,2a,16p,b,16p,8d6,32p,a6,16p,8g6,32p,d6,16p,16c6,32p,16b,32p,2a,16p,b,16p,8d6,32p,a,16p,16g,32p,16a,32p,b,16p,8d6,32p,2a,16p,b,16p,8d6,32p,a6,16p,8g6,16p,2d7";
//char *zelda_ww = "Overworld:d=4,o=5,b=135:1p,8f#,16p,16d,1a.4,16d,16a4,16d,16f#,1a,16a,16p,16g,16f#,1g,1e.,2a4,16b4,16p,16b4,16c#,1d.,e,1d,1a4,16b4,16p,16b4,16c#,1d.,e,1d,1e,8f#,16p,16d,1a.4,16d,16a4,16d,16f#";
//char *ww2 = "Overworld2:d=4,o=5,b=135:1a,16a,16p,16g,16f#,1g,1e.,2a4,16b4,16p,16b4,16c#,1d.,e,2d,1f#.,16d,16p,16d,16e,1f,16d,16p,16d,16e,2f.,1g,1p,8f#,16p,16d,1a.4,8d,16f#,16p,8f#,16e,16d#,1e.,16d,16e,8f#,16p,16d,1a.4,16d,16p,16d,16e,16f#,16g,a.,16g,16f#,1g.,8b,16p";
//char *ww3 = "Overworld3:d=4,o=5,b=135:16g,2d.,1e,1d,1d,16b4,16p,16b4,16c#,2d.,16b4,16p,16b4,16c#,2d.,1c#,1p,8f#,16p,16d,1a.4,8d,16f#,16p,8f#,16e,16d#,1e.,16d,16e,8f#,16p,16d,1a.4,16d,16p,16d,16e,16f#,16g,a.,16g,16f#,1g.,8b,16p,16g,2d.,1e,1d,1d,16a#4,16p,16a#4,16c,2d.,16a#4,16p,16a#4,16c,2d.,1e";
//char *lillium = "lilium_int:d=4,o=5,b=86:2p,f#,c#6,2g#.,a,2a,f#,c#6,2g#.,a,b,a,1f#,g#,e,d,1e,f#,d,c#,d,e,2f#.,g#,a,b,1a,2g#,f#,c#6,2g#.,a,2a,f#,c#6,2g#.,a,b,a,1f#,g#,e,d,1e,f#,d,c#,d,b,a,g#,f#,f,d#,f,f#,a#,b,c#6,p,p,d6,a,p,g#,d6,p,p,c#6,e6,p,p,a,c#6,p,p,c6,a,g#,f#,p,p,2a.,b,p,p,1g#.,f#,c#6,2g#.,a,2a,f#,c#6,2g#.,a,b,a,1f#,g#,e,d,1e,f#,d,c#,d,b,a,g#,f#,f,d#,f,1f#";
//char *act = "missathing:d=4,o=5,b=125:2p,16a,16p,16a,16p,8a.,16p,a,16g,16p,2g,16p,p,8p,16g,16p,16g,16p,16g,8g.,16p,c6,16a#,16p,a,8g,f,g,8d,8f.,16p,16f,16p,16c,8c,16p,a,8g,16f,16p,8f,16p,16c,16p,g,f";
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

void alarm()
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

      Serial.println("2");      
      
      if (song == 3) {
        zelda = "Overworld:d=4,o=5,b=135:1p,8f#,16p,16d,1a.4,16d,16a4,16d,16f#,1a,16a,16p,16g,16f#,1g,1e.,2a4,16b4,16p,16b4,16c#,1d.,e,1d,1a4,16b4,16p,16b4,16c#,1d.,e,1d,1e,8f#,16p,16d,1a.4,16d,16a4,16d,16f#";
        play_rtttl(zelda);
        zelda = "Overworld2:d=4,o=5,b=135:1a,16a,16p,16g,16f#,1g,1e.,2a4,16b4,16p,16b4,16c#,1d.,e,2d,1f#.,16d,16p,16d,16e,1f,16d,16p,16d,16e,2f.,1g,1p,8f#,16p,16d,1a.4,8d,16f#,16p,8f#,16e,16d#,1e.,16d,16e,8f#,16p,16d,1a.4,16d,16p,16d,16e,16f#,16g,a.,16g,16f#,1g.,8b,16p";
        play_rtttl(zelda);
        zelda = "Overworld3:d=4,o=5,b=135:16g,2d.,1e,1d,1d,16b4,16p,16b4,16c#,2d.,16b4,16p,16b4,16c#,2d.,1c#,1p,8f#,16p,16d,1a.4,8d,16f#,16p,8f#,16e,16d#,1e.,16d,16e,8f#,16p,16d,1a.4,16d,16p,16d,16e,16f#,16g,a.,16g,16f#,1g.,8b,16p,16g,2d.,1e,1d,1d,16a#4,16p,16a#4,16c,2d.,16a#4,16p,16a#4,16c,2d.,1e";
        play_rtttl(zelda);
      }
      else if (song == 1) {
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
      if(song > 3) song = 0;      
      delay(50);
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
  if (activada == "1") alarm();
  
  if(Serial.available() > 0) {
    activada = Serial.readString();
    Serial.println(activada);    
  }  
}
