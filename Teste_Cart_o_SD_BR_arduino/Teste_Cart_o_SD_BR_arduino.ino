#include <SD.h>
File arquivoTXT;

void setup()
{
  Serial.begin(9600);
  SD.begin(4);      // o parametro e' o pino conectado ao CS do modulo
  
  arquivoTXT = SD.open("texto.txt", FILE_WRITE);
  if (arquivoTXT) {
    arquivoTXT.println("Teste de arquivos TXT em SD no Arduino");
    arquivoTXT.println("BR-Arduino.org");
     arquivoTXT.close();
    Serial.println("OK.");
  } else {
    Serial.println("Erro ao abrir ou criar o arquivo texto.txt.");
  }
}


void loop(void) { 
}
