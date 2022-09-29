int inPin = 2;
int outPin = 13;

int state = HIGH;
int reading;
int previous = LOW;

long timer = 0;
long debounce = 200;

void setup(){
  pinMode (inPin, INPUT);
  pinMode (outPin, OUTPUT);
}

void loop(){
  reading = digitalRead(inPin);
  
  if (reading == HIGH && previous == LOW && millis() - timer > debounce)
  {
    if (state == HIGH)
      state = LOW;
    else 
      state = HIGH;
    
    timer = millis();
  }
  
  digitalWrite(outPin, state);
  
  previous = reading;
}
