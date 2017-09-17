#include "DHT.h"


#define DHTPIN A9 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
  Serial.begin(9600);
  Serial.println("DHT11 test!");
  dht.begin();

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

    Serial.print(" H");
    Serial.print(h);
    Serial.println();
        
  }
  delay(2000);
}
