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
#define trigPin 9
#define echoPin 8

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "ZSRrSIohgF1ofJhwRwH2Wcqxs8cyymfu";
float pingTime;  
float distance;  
float speedOfSound=776.5;

WidgetTerminal terminal(V1);
BLYNK_WRITE(V1)
{

  // if you type "Marco" into Terminal Widget - it will respond: "Polo:"
  if (String("Marco") == param.asStr()) {
    terminal.println("You said: 'Marco'") ;
    terminal.println("I said: 'Polo'") ;
  } else {

    // Send it back
    terminal.print("You said:");
    terminal.write(param.getBuffer(), param.getLength());
    terminal.println();
  }

  // Ensure everything is sent
  terminal.flush();
}

void setup()
{
  // Debug console
  DebugSerial.begin(9600);

  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  Blynk.begin(Serial, auth);
}

void loop()
{
  digitalWrite(trigPin, LOW);  //Set trigger pin low
  delayMicroseconds(2000);     //Let signal settle
  digitalWrite(trigPin, HIGH); //Set trigPin high
  delayMicroseconds(15);       //Delay in high state
  digitalWrite(trigPin, LOW);  //ping has now been sent

  pingTime = pulseIn(echoPin, HIGH);
  
  Serial.print("pingTime : ");         
  Serial.print(pingTime);
  Serial.println(" microseconds.");
  
  pingTime=pingTime/1000000; //convert pingTime to seconds by dividing by 1000000 (microseconds in a second)
  pingTime=pingTime/3600; //convert pingtime to hours by dividing by 3600 (seconds in an hour)
  distance= speedOfSound * pingTime;  //This will be in miles, since speed of sound was miles per hour
  distance=distance/2; //Remember ping travels to target and back from target, so you must divide by 2 for actual target distance.
  distance = distance*160934;  // distance in cm

  Serial.print("Target Distance: ");
  Serial.print(distance);
  Serial.println(" cm.");
  
  Blynk.run();
}
