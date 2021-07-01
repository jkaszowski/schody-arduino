#include "Arduino.h"

#define pierwszyDol 4
#define pierwszyGora 18
#define czas_miedzy_stopniami 200
#define czas_miedzy_zapaleniem_a_gaszeniem 2000

int progFotokomorki = 100;
int progFotorezystor = 100;

void setup() {
  
  for(byte n = minWejscie; n < maxWejscie; n++){//ustawienie wyjsc
    pinMode(n,OUTPUT);
    digitalWrite(n,HIGH);//wylacz po zadeklarowaniu jako wyjscie
  }

  //fotokomórki
  pinMode(A5,INPUT); //gorna fotokomórka
  pinMode(A6,INPUT); //dolna fotokomórka

  //fotorezystor
  pinMode(A7,INPUT);
}

void loop() {

  if(analogRead(A7)>progFotorezystor){

    if(analogRead(A5) < progFotokomorki){
      //zapalaj od góry do dołu
      for (byte i = pierwszyGora; i >=pierwszyDol ; i--)
      {
        digitalWrite(i,LOW);
        delay(czas_miedzy_stopniami);
      }

      delay(czas_miedzy_zapaleniem_a_gaszeniem);

      //gaś od góry do dołu
      for (byte i = pierwszyGora; i >=pierwszyDol ; i--)
      {
        digitalWrite(i,HIGH);
        delay(czas_miedzy_stopniami);
      }
    }


    if(analogRead(A6) < progFotokomorki){
      //zapalaj od dołu do góry
      for (byte i = pierwszyDol; i <=pierwszyGora ; i++)
      {
        digitalWrite(i,LOW);
        delay(czas_miedzy_stopniami);
      }

      delay(czas_miedzy_zapaleniem_a_gaszeniem);

      //gaś od 
      for (byte i = pierwszyDol; i <=pierwszyGora ; i++)
      {
        digitalWrite(i,HIGH);
        delay(czas_miedzy_stopniami);
      }
    }
  }
}
