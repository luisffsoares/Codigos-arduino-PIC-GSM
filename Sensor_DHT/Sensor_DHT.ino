#include "DHT.h"
#include <SoftwareSerial.h>

#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial mySerial(10, 11); // RX, TX

void setup() 
{
  Serial.begin(9600);
  Serial.println("DHT11 test!");
  dht.begin();
  mySerial.begin(4800);

}
 
void loop() 
{
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
    


  if (isnan(t) || isnan(h)) 
  {
    Serial.println("Failed to read from DHT");
  } 
  else
  { 


    
    Serial.print("T"); 
    Serial.print(t);

    Serial.print("H");
    Serial.print(h);
    Serial.println();
        
    mySerial.print("T"); 
    mySerial.print(t);

    mySerial.print("H");
    mySerial.print(h);
    mySerial.println();
   
  }
  delay(2000);
}
