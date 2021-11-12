// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"
#include <M5Stack.h>
#define DHTPIN 5     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
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
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
  
  M5.begin();
  M5.Power.begin();
  M5.Lcd.setTextColor(YELLOW);  
  M5.Lcd.setTextSize(2);  
  M5.Lcd.println("Pulsa A durante 5s para Centigrados"); 
  M5.Lcd.println("Pulsa B durante 5s para Fahrenheit");
  M5.Lcd.print("\n");
}

void loop() {
  M5.BtnA.read();
  M5.BtnB.read();
  delay(5000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

 
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  int nulo = 0;
  // Check if any reads failed and exit early (to try again).
  if ( isnan(t) | isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(("Temperature: "));
  Serial.print(t);


   M5.update();
   
  if (M5.BtnA.isPressed()){
             M5.Lcd.print("Temperature:");
             M5.Lcd.print(t);
             M5.Lcd.print("\n");
  }else if (M5.BtnB.isPressed()){
            M5.Lcd.print("Fahrenheit:");
            M5.Lcd.print(f);
            M5.Lcd.print("\n");
  }
  
}
