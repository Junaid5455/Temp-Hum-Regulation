

#include "DHT.h"
#include <SoftwareSerial.h>
SoftwareSerial serial (0,1);
unsigned long previousMillis = 0;
//const long interval = 1000;


#define DHTPIN 8     // Digital pin connected to the DHT sensor
#define fan1 2
#define fan2 4
#define fan3 6
#define fan4 7
#define heater1 12
#define heater2 13
unsigned long maxtemp=100;
unsigned long mintemp=0;
unsigned long maxhum=100;
unsigned long minhum=0;
int fanstate1 = LOW;
int fanstate2 = LOW;
int fanstate3 = LOW;
int fanstate4 = LOW;
int heaterstate1 = LOW;
int heaterstate2 = LOW;
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 3 (on the right) of the sensor to GROUND (if your sensor has 3 pins)
// Connect pin 4 (on the right) of the sensor to GROUND and leave the pin 3 EMPTY (if your sensor has 4 pins)
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  serial.begin(9600);
  serial.println(F("DHTxx test!"));
  pinMode(fan1,OUTPUT);
  pinMode(fan2,OUTPUT);
  pinMode(fan3,OUTPUT);
  pinMode(fan4,OUTPUT);
  pinMode(heater1,OUTPUT);
  pinMode(heater2,OUTPUT);

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  
  unsigned long currentMillis = millis();
  if (serial.available()>0)
  {
    String val = serial.readStringUntil('\n');
    if ((val[0]>=48)&&(val[0]<=57))
    {
   char delimiter1 = ',';
   char delimiter2 = ';';
   char delimiter3 = ':';
   int delimiterPos1 = val.indexOf(delimiter1);
   int delimiterPos2 = val.indexOf(delimiter2);
   int delimiterPos3 = val.indexOf(delimiter3);
   String substring1 = val.substring(0, delimiterPos1);
   serial.println(substring1);
   String substring2 = val.substring(delimiterPos1 + 1,delimiterPos2);
   serial.println(substring2);
   String substring3 = val.substring(delimiterPos2 + 1,delimiterPos3);
   serial.println(substring3);
   String substring4 = val.substring(delimiterPos3+1);
   serial.println(substring4);
    
    serial.println(val);
    maxtemp = substring1.toInt();
    mintemp = substring2.toInt();
    maxhum = substring3.toInt();
    minhum = substring4.toInt();
    }
    if(val[0]==65){
       serial.println(val);
    fanstate1= HIGH;
     previousMillis = currentMillis;
      
  }
  if (val[0]==97){
     serial.println(val);
    fanstate1= LOW;
     
  }
  if(val[0]==66){
       serial.println(val);
    fanstate2= HIGH;
     previousMillis = currentMillis;
      
  }
  if (val[0]==98){
     serial.println(val);
    fanstate2= LOW;
     
  }
  if(val[0]==67){
       serial.println(val);
    fanstate3= HIGH;
     previousMillis = currentMillis;
      
  }
  if (val[0]==99){
     serial.println(val);
    fanstate3= LOW;
     
  }
  if(val[0]==68){
       serial.println(val);
    fanstate4= HIGH;
     previousMillis = currentMillis;
      
  }
  if (val[0]==100){
     serial.println(val);
    fanstate4= LOW;
     
  }
  if(val[0]==69){
       serial.println(val);
    heaterstate1= HIGH;
     previousMillis = currentMillis;
      
  }
  if (val[0]==101){
     serial.println(val);
    heaterstate1= LOW;
     
  }
  if(val[0]==70){
       serial.println(val);
    heaterstate2= HIGH;
     previousMillis = currentMillis;
      
  }
  if (val[0]==102){
     serial.println(val);
    heaterstate2= LOW;
     
  }
  }
  if (currentMillis - previousMillis >= 1000) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;


  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

 // Serial.print(F("Humid: "));
  serial.print(h);
  serial.print(";");
  //Serial.println(F("%  "));
 // Serial.print("Temp: ");
  serial.println(t);
  //Serial.println(" ");
  //Serial.println(F("°C "));
  //Serial.print(f);
  //Serial.print(F("°F  Heat index: "));
  //Serial.print(hic);
  //Serial.print(F("°C "));
  //Serial.print(hif);
  //Serial.println(F("°F"));
  
  if (h>maxhum){
    fanstate1= HIGH;
    fanstate2= HIGH;
    fanstate3= HIGH;
    fanstate4= HIGH;
    
  }
  if (h<minhum) {
    fanstate1= LOW;
    fanstate2= LOW;
    fanstate3= LOW;
    fanstate4= LOW;
    
  }
  if (t<mintemp){
    heaterstate1= HIGH;
    heaterstate2= HIGH;
  }
  if (t>maxtemp) {
    heaterstate1= LOW;
    heaterstate2= LOW;
  }
  
  }
  digitalWrite(fan1,fanstate1);
  digitalWrite(fan2,fanstate2);
  digitalWrite(fan3,fanstate3);
  digitalWrite(fan4,fanstate4);
  digitalWrite(heater1,heaterstate1);
  digitalWrite(heater2,heaterstate2);
  
}
