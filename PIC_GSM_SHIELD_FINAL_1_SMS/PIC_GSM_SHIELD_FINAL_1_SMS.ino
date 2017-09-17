#include "SIM900.h"
#include <SoftwareSerial.h>
#include "DHT.h"
#include "sms.h"

#define DHTPIN A15 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);
SMSGSM sms;

int numdata;
boolean started=false;
char smsbuffer[160];
char n[20];

char buffer[110];
char temp[10];
char humi[10];
char num[10];
int x = 5;
int i = 1;
int a = 0;

void setup()
{
     pinMode(16, OUTPUT);
     Serial.begin(9600);
     dht.begin();
     Serial.println("GSM Shield testing.");

     if (gsm.begin(2400)) {
          Serial.println("\nstatus=READY");
          started=true;
     } else Serial.println("\nstatus=IDLE");

     if(started) {
       
          if (sms.SendSMS("0414499606527", "Teste iniciado"))
          Serial.println("\nSMS sent OK");
      
     }
   
};

void loop()
{   
    float h = dht.readHumidity(); 
    float t = dht.readTemperature();
    a=a+1;
    
    dtostrf(t,3,2,temp);  //(descobrir oq isso faz)
    dtostrf(h,3,2,humi);
    dtostrf(a,3,0,num);
    
    
    sprintf(buffer, "%s\nTemperatura: %soC \nHumidade:    %s%%",num, temp,humi); //coloca as variavis do texto
    
    Serial.println("\n");
    Serial.println(buffer);
    
     if(started) {
          digitalWrite(16, HIGH); 
          Serial.println(n);
          Serial.println(smsbuffer);
          sms.SendSMS("0414499121716", buffer);
          sms.SendSMS("0414499606527",buffer);
          Serial.println(buffer);
          delay(900000);
          digitalWrite(16, LOW);
     }
     
}   

