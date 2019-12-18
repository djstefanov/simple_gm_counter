#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const byte interruptPin = 2;
const unsigned long period = 150000; 
unsigned long startMillis;
unsigned long currentMillis;
unsigned long interval;
unsigned long counts;
unsigned long counter = 0;

const char* ssid = "";
const char* password = "";
const char* url = "http://weather.bulair1.eu/saverad.php";
String msg = "";

HTTPClient http;

void handleInterrupt() {
  counter++;
}
 
void setup() {
 
  Serial.begin(115200);

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println(" connected"); 
  
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, RISING);
  startMillis = millis();
  
  Serial.println();
  Serial.println("Setup done.");
}
 
void loop() {
  
  currentMillis = millis();
  
  interval = currentMillis - startMillis;
  if( interval > period ) {
    counts = counter;
    counter = 0;
    
    startMillis = currentMillis;

    msg = String( "{\"interval\":" ) + String( interval ) + ",\"counts\":" + String( counts ) + "}";

    http.begin( url);
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST( msg );
    http.end();
    
    Serial.println( msg );
    Serial.println( httpCode );
    
  }
}
