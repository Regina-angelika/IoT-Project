/* Cara Program Sensor Cahaya LDR 
Dev: teknisibali // Date: 11/11/2019 // www.teknisibali.com */

int sensorPin = A5;
int sensorValue = 0;

void setup (){

  Serial.begin(9600); // Inisialisasi Port serial

}

  void loop(){
    sensorValue=analogRead(sensorPin); //Membaca nilai analog dari pin A5
    Serial.println (sensorValue); //Mencetak hasil pada monitor serial
    float voltage = sensorValue * (5.0/1023.0);
    Serial.println(voltage);

    delay(1000); //Memberi jeda selama 1 detik
}
