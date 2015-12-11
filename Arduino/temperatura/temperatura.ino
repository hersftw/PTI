#define aref_voltage 3.3  

int tempReading; 
float voltage;
float temperatureC;


void temp()
{
  tempReading = analogRead(2);  
 
  // converting that reading to voltage, which is based off the reference voltage
  voltage = tempReading * aref_voltage;
  voltage /= 1024.0;     
  // print out the voltage
  //Serial.print(voltage); Serial.println(" volts");     
  // now print out the temperature
  temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                                   //to degrees ((volatge - 500mV) times 100)
  Serial.println(temperatureC);      
      
  //Serial.print(temperatureC); blue.println(" degrees C");     
}
 
void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL);
  //Serial.println("Conectado");
}
 
void loop() 
{   
  if(Serial.available() > 0)
  {
    String req = Serial.readString();
    if(req == "1") temp();
  } 
}
