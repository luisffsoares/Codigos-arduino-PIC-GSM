#include "SIM900.h"
#include <SoftwareSerial.h>
#include "inetGSM.h"
#include "DHT.h"
#include "sms.h"
//#include "call.h"

//To change pins for Software Serial, use the two lines in GSM.cpp.

//GSM Shield for Arduino
//www.open-electronics.org
//this code is based on the example of Arduino Labs.

//Simple sketch to start a connection as client.

InetGSM inet;
//CallGSM call;
//SMSGSM sms;

char msg[50];
int numdata;
char inSerial[50];
int i=0;
boolean started=false;

void setup()
{
     //Serial connection.
     Serial.begin(9600);
     Serial.println("GSM Shield testing.");
     //Start configuration of shield with baudrate.
     //For http uses is raccomanded to use 4800 or slower.
     if (gsm.begin(2400)) {
          Serial.println("\nstatus=READY");
          started=true;
     } else Serial.println("\nstatus=IDLE");

     if(started) {
          //GPRS attach, put in order APN, username and password.
          //If no needed auth let them blank.
          if (inet.attachGPRS("internet.wind", "", ""))
               Serial.println("status=ATTACHED");
          else Serial.println("status=ERROR");
          delay(1000);

          //Read IP address.
          gsm.SimpleWriteln("AT+CIFSR");
          delay(5000);
          //Read until serial buffer is empty.
          gsm.WhileSimpleRead();

          //Sites p/ tentar:
          //https://www.google.com.br/search?q=teste&oq=teste&aqs=chrome..69i57j69i60l3j0j69i65.1341j0j7&sourceid=chrome&ie=UTF-8
          //http://lffs-teste-ic-cnt-br.umbler.net/adiciona_valor_teste.php?CODIGO=1&TEMP=%s&HUMI=%s&DATA_HORA=%s&OBS=teste_raspberry
          //adiciona_valor_teste.php?CODIGO=0&TEMP=14&HUMI=57&DATA_HORA=00%3A13++SEXTA&OBS=teste_live_online
          
          //TCP Client GET, send a GET request to the server and
          //save the reply.

          numdata=inet.httpGET("lffs-teste-ic-cnt-br.umbler.net", 80, "/adiciona_valor_teste.php?CODIGO=0&TEMP=13&HUMI=55&DATA_HORA=00:18++SEXTA&OBS=teste_arduino", msg, 50);
          //numdata=inet.httpGET("lffs-teste-ic-cnt-br.umbler.net", 80, "/teste.html", msg, 50);
          //numdata=inet.httpGET("www.google.com", 80, "/search?q=open-electronics&oq=open-electronics&ie=UTF-8", msg, 50);
          //Print the results.
          Serial.println("\nNumber of data received:");
          Serial.println(numdata);
          Serial.println("\nData received:");
          Serial.println(msg);
     }
};

void loop()
{
     //Read for new byte on serial hardware,
     //and write them on NewSoftSerial.
     serialhwread();
     //Read for new byte on NewSoftSerial.
     serialswread();
};

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
