#include <ESP8266WiFi.h>

const char* ssid = "YourNetworkName";
const char* password = "YourNetworkPassword";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
}

void loop() {
  // Do something here
}
