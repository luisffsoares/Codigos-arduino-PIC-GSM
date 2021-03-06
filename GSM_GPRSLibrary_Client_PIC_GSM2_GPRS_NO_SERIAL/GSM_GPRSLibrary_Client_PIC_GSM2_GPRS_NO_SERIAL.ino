#include "SIM900.h"
#include <SoftwareSerial.h>
#include "inetGSM.h"
#include "DHT.h"
#include <DS1307.h>
//#include "sms.h"
//#include "call.h"
//To change pins for Software Serial, use the two lines in GSM.cpp.

#define DHTPIN A9 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);
DS1307 rtc(A14, A15);

InetGSM inet;
//CallGSM call;
//SMSGSM sms;

char msg[50];
int numdata;
char inSerial[50];
int i=0;
int n=1;
boolean started=false;
//char REQ_GET[11] = "/teste.html";

void setup()
{
  //Aciona o relogio
  rtc.halt(false);
   
  //As linhas abaixo setam a data e hora do modulo
  //e podem ser comentada apos a primeira utilizacao
 // rtc.setDOW(SATURDAY);      //Define o dia da semana
 //rtc.setTime(15, 21, 35);     //Define o horario
  //rtc.setDate(22, 07, 2017);   //Define o dia, mes e ano
   
  //Definicoes do pino SQW/Out
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);
       
 // Serial.begin(9600);
 // Serial.println("***INICIO DO TESTE***");
  dht.begin();
  //Serial.println("***INICIO DO  REQUEST***");
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  //  URL(request)--> /adiciona_valor_teste.php?CODIGO=0&TEMP=13&HUMI=55&DATA_HORA=00:18++SEXTA&OBS=teste_arduino
  String URL = "/adiciona_valor_teste.php?CODIGO=0&TEMP=";
  // testa se retorno é valido, caso contrário algo está errado
//  if (isnan(t) || isnan(h)) 
 // {
//    Serial.println("Failed to read from DHT");
//  } 
 // else
 // { 
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
    char REQ_GET[len];
    URL.toCharArray(REQ_GET,len);   
 //   Serial.println(REQ_GET);
 // }

 
  //   Serial.println("GSM Shield testing.");
     //Start configuration of shield with baudrate.
     //For http uses is raccomanded to use 4800 or slower.
     if (gsm.begin(2400)) {
  //        Serial.println("\nstatus=READY");
          started=true;
     } else //Serial.println("\nstatus=IDLE");

    if(started) {
          //GPRS attach, put in order APN, username and password.
          //If no needed auth let them blank.
          if (inet.attachGPRS("internet.wind", "", "")){
     //          Serial.println("status=ATTACHED");
    } //Serial.println("status=ERROR");
          delay(1000);

          //Read IP address.
          gsm.SimpleWriteln("AT+CIFSR");
          delay(5000);
          //Read until serial buffer is empty.
          gsm.WhileSimpleRead();

          //TCP Client GET, send a GET request to the server and
          //save the reply.
          numdata=inet.httpGET("lffs-teste-ic-cnt-br.umbler.net", 80, REQ_GET, msg, 50);
          //Print the results.
       //   Serial.println("\nNumber of data received:");
       //   Serial.println(numdata);
       //   Serial.println("\nData received:");
       //   Serial.println(msg);
     }

     
/*     
 for(i = 0;i<=10;i++){
     //Read for new byte on serial hardware,
     //and write them on NewSoftSerial.
     serialhwread();
     //Read for new byte on NewSoftSerial.
    serialswread();
  }
  */
}

void loop()
{

for (int i=0;i<2*60;i++){
 // Serial.print(".");
  delay(1000);
}
  Serial.println();

//  Serial.print("***INICIO DO LOOP*** ");
//  Serial.println(n);
  n = n+1;
  float h = dht.readHumidity();
  float t = dht.readTemperature();
   String URL = "/adiciona_valor_teste.php?CODIGO=0&TEMP=";
 
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
    char REQ_GET[len];
    URL.toCharArray(REQ_GET,len);



     numdata=inet.httpGET("lffs-teste-ic-cnt-br.umbler.net", 80, REQ_GET, msg, 50);
     //Print the results.
 //    Serial.println("\nNumber of data received:");
 //    Serial.println(numdata);
 //    Serial.println("\nData received:");
 //    Serial.println(msg);
}
/*
void serialhwread()
{
     i=0;
     if (Serial.available() > 0) {
          while (Serial.available() > 0) {
               inSerial[i]=(Serial.read());
               delay(10);
               i++;
          }

          inSerial[i]='\0';
          if(!strcmp(inSerial,"/END")) {
               Serial.println("_");
               inSerial[0]=0x1a;
               inSerial[1]='\0';
               gsm.SimpleWriteln(inSerial);
          }
          //Send a saved AT command using serial port.
          if(!strcmp(inSerial,"TEST")) {
               Serial.println("SIGNAL QUALITY");
               gsm.SimpleWriteln("AT+CSQ");
          }
          //Read last message saved.
          if(!strcmp(inSerial,"MSG")) {
               Serial.println(msg);
          } else {
               Serial.println(inSerial);
               gsm.SimpleWriteln(inSerial);
          }
          inSerial[0]='\0';
     }
}

void serialswread()
{
     gsm.SimpleRead();
}

*/

