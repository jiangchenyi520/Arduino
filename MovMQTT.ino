#include <M5Stack.h>
#include <WiFi.h>
#include <Wire.h>
#include <ArduinoMqttClient.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#if defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_AVR_UNO_WIFI_REV2)
  #include <WiFiNINA.h>
#elif defined(ARDUINO_SAMD_MKR1000)
  #include <WiFi101.h>
#elif defined(ARDUINO_ESP8266_ESP12)
  #include <ESP8266WiFi.h>
#endif


WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
long lastMsg = 0;
char msg[50];
//int value = 0;

char ssid[] = "HUAWEI-104LE0"  ;    // your network SSID (name)
char pass[] = "2021Esunamierda"  ;// your network password (use for WPA, or use as key for WEP)

//ip de la raspberry
const char* mqtt_server = "";


const char broker[] = "broker.hivemq.com";
int        port     = 1883;
const char topic[]  = "eskrip/practica/";

const long interval = 1000;
unsigned long previousMillis = 0;

int count = 0;
int pirState = HIGH; 
int val = 0; 

const int PIRPin= 5;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  // You can provide a unique client ID, if not set the library uses Arduino-millis()
  // Each client must have a unique client ID
  mqttClient.setId("1225845");

  // You can provide a username and password for authentication
  // mqttClient.setUsernamePassword("username", "password");

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}


void loop() {
  // call poll() regularly to allow the library to send MQTT keep alives which
  // avoids being disconnected by the broker
  mqttClient.poll();
  int value = digitalRead(PIRPin);

  // avoid having delays in loop, we'll use the strategy from BlinkWithoutDelay
  // see: File -> Examples -> 02.Digital -> BlinkWithoutDelay for more info
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    // save the last time a message was sent
    previousMillis = currentMillis;

    if (value == HIGH)
  {
    Serial.println("Esta movimiento");
        // send message, the Print interface can be used to set the message contents
    mqttClient.beginMessage(topic);
    mqttClient.print("Esta movimiento");
//    mqttClient.print(count);
    mqttClient.endMessage();
    delay(60000);
  }
  else
  {
    Serial.println("No esta movimiento");
    // send message, the Print interface can be used to set the message contents
    mqttClient.beginMessage(topic);
    mqttClient.print("No esta movimiento");
//    mqttClient.print(count);
    mqttClient.endMessage();
    delay(1000);
  }

//    Serial.print("Sending message to topic: ");
//    Serial.println(topic);
//    Serial.print("hello ");
//    Serial.println(count);

    Serial.println();

    count++;
  }


}
