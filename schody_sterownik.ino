void setup() {
  
  for(byte n = 2; n < 18; n++){//ustawienie wyjsc
    pinMode(n,OUTPUT);
    digitalWrite(n,HIGH);//wylacz po zadeklarowaniu jako wyjscie
  }

  //fotokomórki
  pinMode(A5,INPUT);
  pinMode(A6,INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
