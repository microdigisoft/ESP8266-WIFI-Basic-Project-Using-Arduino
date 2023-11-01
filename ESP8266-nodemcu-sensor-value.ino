#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "newindex.h"  //Web page header file

ESP8266WebServer server(80); //Server on port 80

//Enter your SSID and PASSWORD
const char* ssid = "xxxxxx";
const char* password = "xxxx";
const int ledPin = 5;
const int ldrPin = A0;
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
 
void handleLDR() {
  int ldrStatus = analogRead(ldrPin);

  if (ldrStatus <= 10) {

    digitalWrite(ledPin, HIGH);
    Serial.print(ldrStatus);
    Serial.print("LED is ON");
    Serial.println("");
    delay(1000);
  }

  else {
    Serial.print(ldrStatus);
    digitalWrite(ledPin, LOW);
    Serial.println("LED is OFF");
    Serial.println("");
    delay(1000);
 //int a = analogRead(A0);
 String ldrValue = String(ldrStatus);
 
 server.send(200, "text/plane", ldrValue); //Send ADC value only to client ajax request
}
}
//===============================================================
// Setup
//===============================================================

void setup(void){
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");

/*
//ESP32 As access point
  WiFi.mode(WIFI_AP); //Access Point mode
  WiFi.softAP(ssid, password);
*/
//ESP32 connects to your wifi -----------------------------------
  WiFi.mode(WIFI_STA); //Connectto your wifi
  WiFi.begin(ssid, password);

  Serial.println("Connecting to ");
  Serial.print(ssid);

  //Wait for WiFi to connect
  while(WiFi.waitForConnectResult() != WL_CONNECTED){      
      Serial.print(".");
  }
    
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
//----------------------------------------------------------------
 
  server.on("/", handleRoot);      //This is display page
  server.on("/readLDR", handleLDR);//To get update of ADC Value only
 
  server.begin();                  //Start server
  Serial.println("HTTP server started");

  pinMode(ledPin, OUTPUT);

  pinMode(ldrPin, INPUT);
}

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void loop(void){
  server.handleClient();
  delay(1);

  
}
