void setup() {
  // put your setup code here, to run once:
 /*
    //Timer 0
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    TCCR0A = 
    TccR0B = 
    OCR0A =
    OCR0B = 
*/

    //Timer 2
    pinMode(3, OUTPUT);
    pinMode(11, OUTPUT);
    TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
    TCCR2B = _BV(CS20);// [1]
    OCR2A = 100;
    OCR2B = 50;
  
}

void loop() {
  // put your main code here, to run repeatedly:

}

/*
[1] : la frequence d'horloge ne possède pas de préscalaire, la fc de 16MHz de la carte arduino est juste diviser par le timer de 8bit donc 16.10^6/256=62500Hz


*/
