int trigPin=9;  //Sensor Trigger pin connected to Arduino pin 13
int echoPin=8;  //Sensor Echo pin connected to Arduino pin 11
float pingTime;  //time for ping to travel from sensor to target and return
float distance;  //Distance to Target in inches
float speedOfSound=776.5; //Speed of sound in miles per hour
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);        // Initialize serial monitor
  pinMode(trigPin, OUTPUT);  // Set trigger pin as an output pin
  pinMode(echoPin, INPUT);   // Set echo pin as an output pin
}
 
void loop() {
  // put your main code here, to run repeatedly:
  // Generate a high signal for min. 10us to give trigger to sensor   
  digitalWrite(trigPin, LOW);  //Set trigger pin low
  delayMicroseconds(2000);     //Let signal settle
  digitalWrite(trigPin, HIGH); //Set trigPin high
  delayMicroseconds(15);       //Delay in high state
  digitalWrite(trigPin, LOW);  //ping has now been sent
 
  // Capture the High Width Pulse on Echo pin to calculate the travel time (pingTime) of a wave. 
  // pulseIn() function calculates the time from width of pulse 
  pingTime = pulseIn(echoPin, HIGH);  //pingTime is presented in microceconds
 
  //Print pingTime on Serial Monitor
  Serial.print("pingTime : ");         
  Serial.print(pingTime);
  Serial.println(" microseconds.");            
 
  // Do conversation in units and Calculate Distance in cm using formula
  pingTime=pingTime/1000000; //convert pingTime to seconds by dividing by 1000000 (microseconds in a second)
  pingTime=pingTime/3600; //convert pingtime to hours by dividing by 3600 (seconds in an hour)
  distance= speedOfSound * pingTime;  //This will be in miles, since speed of sound was miles per hour
  distance=distance/2; //Remember ping travels to target and back from target, so you must divide by 2 for actual target distance.
  distance = distance*160934;  // distance in cm
 
  // Print distance on Serial Monitor
  Serial.print("Target Distance: ");
  Serial.print(distance);
  Serial.println(" cm.");
  delay(300);
}
