#include <ESP8266WiFi.h>
#include "Pushover.h" // Push notification library

const char* ssid = "MIT";
const char* password = "";

// Time to sleep (in seconds):
const int sleepTimeS = 5;

int fsrAnalogPin = 0; // FSR is connected to analog 0
int fsrReading;      // the analog reading from the FSR resistor divider
int testDelay = 20;  // in tens of a second  
int fsrThreshold = 250;

void setup() 
{
  long n=0;
  pinMode(2, OUTPUT); //LED PIN
  do {
      fsrReading = analogRead(fsrAnalogPin);
      n=n+1;
      digitalWrite(2, LOW); 
      delay(100);
     } while(fsrReading >= fsrThreshold);

  if (n >= testDelay) {
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) delay(50);
      Pushover po = Pushover("asxfwkh6gkmk5xzv72ann2avyn8i9g","ucx3ovf3y6k32cwfj52nnxjna8qspu");
        po.setDevice("LRSM-iPhone");
        po.setTitle("GlucoTrack");
        po.setMessage("Help your doctor track your glucose here!");
        po.setSound("bike");
        po.setUrl("https://www.surveymonkey.com/r/?sm=60q38EmkzQJ65sJkFJRWSlovrogLF3K4xxUI1VmHQA4_3D");
        po.setUrlTitle("Your GlucoTrack Site");
        po.send()==1;
        delay(1000);
        digitalWrite(2, HIGH);
        //Serial.begin(115200);
        //if (po.send()==1){Serial.println("Notification was sent!");}
        //else {Serial.println("Notification failed =(");}
      }  
     
    // Sleep
    //Serial.println("ESP8266 is in sleep mode");
    ESP.deepSleep(sleepTimeS * 1000000);
}

void loop() 
{
}



