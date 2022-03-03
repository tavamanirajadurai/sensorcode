//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
// Set these to run example.
#define FIREBASE_HOST "accident-notifier-efbca-default-rtdb.firebaseio.com"                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "9p2xcdMzatQoQuDWIPgLQPDRmr5lk2lTAJQtsTA4" //Your Firebase Database Secret goes here



#define WIFI_SSID "Durai"                                               //WiFi SSID to which you want NodeMCU to connect
#define WIFI_PASSWORD "durai durai" 

 
int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED13 = 13;   //  The on-board Arduion LED


int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;
void setup() {
   pinMode(LED13,OUTPUT);         // pin that will blink to your heartbeat!  
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  
}

int n = 0;

void loop() {
   Signal = analogRead(PulseSensorPurplePin);
   if(Signal>450 && Signal<550){
     Firebase.setString("gK5GleiE05bJ2kt5atS9ypx6rnv1/h", "optimal");
   }
   else{
      Firebase.setString("gK5GleiE05bJ2kt5atS9ypx6rnv1/h", "not normal");
   }
  
  
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(3000);
  
 // String name = Firebase.pushInt("logs", n++);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  
  
}
