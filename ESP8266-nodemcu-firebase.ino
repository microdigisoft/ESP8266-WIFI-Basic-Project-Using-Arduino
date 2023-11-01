#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "<Your-Firebase-Host-ID>"
#define FIREBASE_AUTH "<Your-Firebase-API-Key>"
#define WIFI_SSID "<Your-WiFi-SSID>"
#define WIFI_PASSWORD "<Your-WiFi-Password>"

const int ledPin = D1; // Pin connected to the LED

void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  // Set the LED pin as an OUTPUT
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Read the Firebase database value to control the LED
  FirebaseObject ledStatus = Firebase.get("/ledStatus");
  if (ledStatus.success()) {
    int status = ledStatus.getInt();
    digitalWrite(ledPin, status); // Turn the LED on or off based on Firebase value
  } else {
    Serial.println("Failed to get LED status from Firebase");
  }

  // You can add more code here if needed

  delay(1000); // Wait for a moment before checking Firebase again
}
