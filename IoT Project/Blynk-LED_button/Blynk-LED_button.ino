/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  =>
  =>          USB HOWTO: http://tiny.cc/BlynkUSB
  =>

  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT DebugSerial


// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX

#include <BlynkSimpleStream.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "fCNtpF7nGkhMKSoylI3WQhtWHapjthqx";

#define ledPin 13 
#define buttonPin 2
int state = LOW;
int reading;
int previous = HIGH;

long time = 0;
long debounce = 200;

void setup()
{
  // Debug console
  DebugSerial.begin(9600);

  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  Blynk.begin(Serial, auth);
  pinMode (buttonPin, INPUT);
  pinMode (ledPin, OUTPUT);
}

void loop()
{
  Blynk.run();
  reading = digitalRead(buttonPin);
  
  if (reading == LOW && previous == HIGH && millis() - time > debounce)
  {
    if (state == LOW){
      state = HIGH;
      Blynk.notify("LED ON");
    }
    else {
      state = LOW;
      Blynk.notify("LED OFF");
    }
    time = millis();
}
  
  digitalWrite(ledPin, state);
  
  previous = reading;
}
