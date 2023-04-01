#define pinPotentiometre A1

//variable
uint8_t tensionPotentiometre = 0;

void setup() {
  pinMode(3, OUTPUT);   // sortie Timer B
  cli();                // Désactive l'interruption globale
  TCCR2A = 0b00100011;  //00=> OCOA deconnecter(COM2A1:0), 10=> sortie OCOB non inverseuse(COM2B1:0), 00=> reserver, 11=> Fast PWM(WGM01:00)
  TCCR2B = 0b00001010;  //00=> utiliser pour mode non pwm (FOC2A:FOC2B), 00=> reserver, 1=> Fast PWM(WGM02), 010=> diviseur de 8 pour la clock (CS00:01:02)

  OCR2A = 38;  //valeur max du comparateur
  OCR2B = 15;  //valeur a comparer (duty cycle 0 to OCR2A)
  sei();       // Active l'interruption globale

  Serial.begin(9600);
}

void loop() {
  /*
  tensionPotentiometre = analogRead(pinPotentiometre);//on lit la valeur analogique du potentiometre
  OCR2B = (OCR2A / 255) *tensionPotentiometre;
 */

  for (int i = 2; i <= 13; i++) {
    OCR2B = (OCR2A / 15.0) * i;  //on multipli la valeur du potentiometre de anière à fair varier le duty cycle
    delay(2000);
  }
}