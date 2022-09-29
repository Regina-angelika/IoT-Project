int led = 13;
int pir = 2;

int sensorState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(pir, INPUT);
}

void loop() {
  sensorState = digitalRead(pir);
  if(sensorState==HIGH){
    digitalWrite(led, HIGH);
    Serial.println("motion detected");
    delay(5000);
    } else if (sensorState==LOW){
    digitalWrite(led, LOW);
    Serial.println("no motion detected");
  }
}
