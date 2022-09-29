/**************************************************************
 * IoT Motion Detector with Blynk
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 * 
 * Developed by Marcelo Rovai - 30 November 2016
 **************************************************************/
#include <ESP8266WiFi.h>

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <BlynkSimpleEsp8266.h>
char auth[] = "65d9cf145e7a442291c612f24e1df68b";

/* WiFi credentials */
char ssid[] = "ROVAI TIMECAP";
char pass[] = "mjr747@1";

/* HC-SR501 Motion Detector */
#define ledPin D7 
#define pirPin D1 // Input for HC-S501
int pirValue; // Place to store read PIR Value
int motionDetected = 0;

void setup()
{
  Serial.begin(115200);
  delay(10);
  Blynk.begin(auth, ssid, pass);
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  digitalWrite(ledPin, LOW);
}

void loop()
{
  getPirValue();
  Blynk.run();
}

/***************************************************
 * Get PIR data
 **************************************************/
void getPirValue(void)
{
  pirValue = digitalRead(pirPin);
  if (pirValue) 
  { 
    Serial.println("==> Motion detected");
    Blynk.notify("T==> Motion detected");  
  }
  
  digitalWrite(ledPin, pirValue);
}


