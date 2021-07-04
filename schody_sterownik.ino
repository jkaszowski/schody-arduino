#include "Arduino.h"
#include "Timers.h"

#define pierwszyDol 4
#define pierwszyGora 17

#define ON 1
#define OFF 0

#define fotokomorkaGora A4
#define fotokomorkaDol A5

//zmienne globalne dot. czasów
#define interwal 50
int czas_miedzy_stopniami_zapalanie = 200;
int czas_miedzy_stopniami_gaszenie = 200;
int czas_miedzy_zapaleniem_a_gaszeniem = 2000;

int progFotokomorki = 512;
int progFotorezystor = 100;

void setup() {
  
  for(byte n = pierwszyDol; n < pierwszyGora; n++){//ustawienie wyjsc
    pinMode(n,OUTPUT);
    digitalWrite(n,OFF);//wylacz po zadeklarowaniu jako wyjscie
  }

  pinMode(1,INPUT_PULLUP);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  delay(200);

  //jeśl zwarto D1 do masy, ustaw config na 1 wejdź do pętli
  bool config = 0;
  config = !digitalRead(1);

  Timer mojTimer;
  if(config){
    mojTimer.begin(500);
  }

while(config){


    // 0 -zmieniaj czas między stopniami podczas zapalania
    // 1 - zmieniaj czas między stopniami podzczas gaszenia
    // 2 - zmieniaj czas  między zapaleniem a gaszeniem
    byte stan = 0; // przechowuje informacje co teraz ustawiamy

    switch (stan)
    {
    //czas między stopniami podczas zapalania
    case 0:
      if(digitalRead(2)==0){//zwiekszaj
        czas_miedzy_stopniami_zapalanie += interwal;
      }else if(digitalRead(3)==0){//zmniejszaj
        czas_miedzy_stopniami_zapalanie -= interwal;
      }
      break;
    //czas między stopniami podzczas gaszenia
    case 1:
      if(digitalRead(2)==0){
        czas_miedzy_stopniami_gaszenie += interwal;
      }else if(digitalRead(3)==0){
        czas_miedzy_stopniami_gaszenie -= interwal;
      }
      break;
    //czas  między zapaleniem a gaszeniem
    case 2:
      if(digitalRead(2)==0){
        czas_miedzy_zapaleniem_a_gaszeniem += interwal;
      }else if(digitalRead(3)==0){
        czas_miedzy_zapaleniem_a_gaszeniem -= interwal;
      }
      break;
    default://zapisz do EEPROM i wyjdz z trybu konfiguracji
      config = 0;
      break;
    }

    if(digitalRead(1) == 0){
      stan++;
      delay(500);
    }

    //jeśli timer skończył liczyć, zmień stan diody na module
    if(mojTimer.available()){
      digitalWrite(13, !digitalRead(13));
      mojTimer.restart();
    }

  }
}

void loop() {

  //if(analogRead(A7)>progFotorezystor){

    if(analogRead(fotokomorkaGora) < progFotokomorki){
      //zapalaj od góry do dołu
      for (byte i = pierwszyGora; i >=pierwszyDol ; i--)
      {
        digitalWrite(i,ON);
        delay(czas_miedzy_stopniami_zapalanie);
      }

      delay(czas_miedzy_zapaleniem_a_gaszeniem);

      //gaś od góry do dołu
      for (byte i = pierwszyGora; i >=pierwszyDol ; i--)
      {
        digitalWrite(i,OFF);
        delay(czas_miedzy_stopniami_gaszenie);
      }
    }


    if(analogRead(fotokomorkaDol) < progFotokomorki){
      //zapalaj od dołu do góry
      for (byte i = pierwszyDol; i <=pierwszyGora ; i++)
      {
        digitalWrite(i,ON);
        delay(czas_miedzy_stopniami_zapalanie);
      }

      delay(czas_miedzy_zapaleniem_a_gaszeniem);

      //gaś od dołu do góry
      for (byte i = pierwszyDol; i <=pierwszyGora ; i++)
      {
        digitalWrite(i,OFF);
        delay(czas_miedzy_stopniami_gaszenie);
      }
    }
  //}
}
