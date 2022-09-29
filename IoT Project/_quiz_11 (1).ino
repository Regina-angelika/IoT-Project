int buttonPin = 7;
int redLedCar = 13;
int yellowLedCar = 12;
int greenLedCar = 11;
int redLedPedestrian = 3;
int greenLedPedestrian = 2;

int buttonState = 0;

void setup(){
  pinMode(yellowLedCar, OUTPUT);
  pinMode(redLedCar, OUTPUT);
  pinMode(greenLedPedestrian, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(greenLedCar, HIGH);
  digitalWrite(redLedPedestrian, HIGH);
}

void loop(){
  buttonState = digitalRead(buttonPin);
 
  if(buttonState == HIGH){
    digitalWrite(greenLedPedestrian, HIGH);
    digitalWrite(redLedPedestrian, LOW);
    digitalWrite(greenLedCar, LOW);
    digitalWrite(yellowLedCar, HIGH);
    digitalWrite(redLedCar, LOW);
    delay(1000);
   
    digitalWrite(greenLedPedestrian, HIGH);
    digitalWrite(redLedPedestrian, LOW);
    digitalWrite(greenLedCar, LOW);
    digitalWrite(yellowLedCar, LOW);
    digitalWrite(redLedCar, HIGH);
    delay(1000);
  

  } else {
    digitalWrite(greenLedCar, HIGH);
    digitalWrite(redLedPedestrian, HIGH);
    digitalWrite(redLedCar, LOW);
    digitalWrite(greenLedPedestrian, LOW);
  }
}