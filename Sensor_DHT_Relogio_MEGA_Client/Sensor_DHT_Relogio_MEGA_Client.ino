#include "DHT.h"
#include <DS1307.h>
#include <SD.h>

#define DHTPIN A9 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);
DS1307 rtc(A14, A15);

void setup() 
{
  //Aciona o relogio
  rtc.halt(false);
   
  //As linhas abaixo setam a data e hora do modulo
  //e podem ser comentada apos a primeira utilizacao
  rtc.setDOW(FRIDAY);      //Define o dia da semana
  rtc.setTime(12, 39, 35);     //Define o horario
  rtc.setDate(21, 07, 2017);   //Define o dia, mes e ano
   
  //Definicoes do pino SQW/Out
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);
  
  Serial.begin(9600);
  Serial.println("DHT11 test!");
  dht.begin();

}
 
void loop() 
{ 
  /* //Mostra as informações no Serial Monitor
  Serial.print("Hora : ");
  Serial.print(rtc.getTimeStr());
  Serial.print(" ");
  Serial.print("Data : ");
  Serial.print(rtc.getDateStr(FORMAT_SHORT));
  Serial.print(" ");
  Serial.println(rtc.getDOWStr(FORMAT_SHORT));
  */
  
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  //  URL(request)--> /adiciona_valor_teste.php?CODIGO=0&TEMP=13&HUMI=55&DATA_HORA=00:18++SEXTA&OBS=teste_arduino
  String URL = "/adiciona_valor_teste.php?CODIGO=0&TEMP=";
  // testa se retorno é valido, caso contrário algo está errado
  if (isnan(t) || isnan(h)) 
  {
    Serial.println("Failed to read from DHT");
  } 
  else
  { 

    char tmp[4];
    dtostrf(t,1,2,tmp);
    URL = URL + tmp + "&HUMI=";
    
    char humi[10];
    dtostrf(h,1,2,humi);
    URL = URL + humi + "&DATA_HORA=";

    String hora = rtc.getTimeStr();
    String data = rtc.getDateStr(FORMAT_SHORT);
    String horadata = hora+ "++" + data;
    URL = URL + horadata + "&OBS=teste_arduino";
    int len =URL.length()+1;
    Serial.print(URL);
    Serial.print("   ");
    Serial.print(len);
    Serial.println();

    char REQ_GET[len];
    URL.toCharArray(REQ_GET,len);

    Serial.println("Exhibindo char");
    Serial.print(REQ_GET);
    Serial.println();
    Serial.println("cabou");
    String teste = "\teste.html";
    int lenteste =teste.length()+1;
    Serial.println(lenteste);
  }
  delay(2000);
}
