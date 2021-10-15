#include <Adafruit_NeoPixel.h>


const int PIN= 3 ;
int NUMPIXELS=16; //Número de leds conectados
const int PIRPin= 5;
int pirState = HIGH;           // de inicio no hay movimiento
int val = 0; 

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  pinMode(PIN, OUTPUT);
  pinMode(PIRPin, INPUT);
  
      pixels.begin(); // Inicialización
      pixels.show(); // Inicialitza tots els pixels apagats
  Serial.begin(115200);
}
void loop()
{
  int value= digitalRead(PIRPin);
 
  if (value == HIGH)
  {
    Serial.println("Esta movimiento");
    //digitalWrite(LEDPin, HIGH);
    
rainbowCycle(1);//Ciclo de arcoiris progresivo en cada pixel
    delay(500);
  }
  else
  {
    for(int i=0; i< pixels.numPixels(); i++) {
      pixels.setPixelColor(i, 0);
    }
    pixels.show();
    Serial.println("No esta movimiento");
    //digitalWrite(LEDPin, LOW);
    delay(500);
  }
}

 void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
