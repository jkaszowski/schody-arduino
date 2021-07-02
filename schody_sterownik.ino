#include "Arduino.h"

#define pierwszyDol 4
#define pierwszyGora 17
#define czas_miedzy_stopniami 200
#define czas_miedzy_zapaleniem_a_gaszeniem 2000

#define ON 1
#define OFF 0

#define fotokomorkaGora A4
#define fotokomorkaDol A5
int progFotokomorki = 512;
int progFotorezystor = 100;

void setup() {
  
  for(byte n = pierwszyDol; n < pierwszyGora; n++){//ustawienie wyjsc
    pinMode(n,OUTPUT);
    digitalWrite(n,OFF);//wylacz po zadeklarowaniu jako wyjscie
  }

  //fotokomórki
  //pinMode(fotokomorkaGora,INPUT); //gorna fotokomórka
  //pinMode(fotokomorkaDol,INPUT); //dolna fotokomórka

  //fotorezystor
  pinMode(A7,INPUT);
}

void loop() {

  //if(analogRead(A7)>progFotorezystor){

    if(analogRead(fotokomorkaGora) < progFotokomorki){
      //zapalaj od góry do dołu
      for (byte i = pierwszyGora; i >=pierwszyDol ; i--)
      {
        digitalWrite(i,ON);
        delay(czas_miedzy_stopniami);
      }

      delay(czas_miedzy_zapaleniem_a_gaszeniem);

      //gaś od góry do dołu
      for (byte i = pierwszyGora; i >=pierwszyDol ; i--)
      {
        digitalWrite(i,OFF);
        delay(czas_miedzy_stopniami);
      }
    }


    if(analogRead(fotokomorkaDol) < progFotokomorki){
      //zapalaj od dołu do góry
      for (byte i = pierwszyDol; i <=pierwszyGora ; i++)
      {
        digitalWrite(i,ON);
        delay(czas_miedzy_stopniami);
      }

      delay(czas_miedzy_zapaleniem_a_gaszeniem);

      //gaś od 
      for (byte i = pierwszyDol; i <=pierwszyGora ; i++)
      {
        digitalWrite(i,OFF);
        delay(czas_miedzy_stopniami);
      }
    }
  //}
}
