int sensorValue;

void setup(){
Serial.begin(9600);
}

void loop(){
sensorValue = analogRead(A0);
Serial.println(sensorValue);
delay(2000);
}
