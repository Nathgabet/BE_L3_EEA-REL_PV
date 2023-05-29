//variable
float tension =0;
float courant =0;
float pInst =0;
float pPrec =0;

int PWM =50;

void setup() {
  initTimer2(); //initialisation du timer2
  Serial.begin(9600);
}

void loop() {
  tension = (0.22/255)*analogueRead(A0);  //lecture de la tension
  courant =0; //lecture du courant

  MPPT(tension, courant, &pInst, &pPrec, &PWM); //recherche du point MPPT
  OCR2B = (OCR2A / 100.0) *PWM; //modification du PWM de sortie
}

//-------------------------fonction cree-------------------------
void initTimer2(){
  pinMode(3, OUTPUT);   // sortie Timer B
  cli();                // Désactive l'interruption globale
  TCCR2A = 0b00100011;  //00=> OCOA deconnecter(COM2A1:0), 10=> sortie OCOB non inverseuse(COM2B1:0), 00=> reserver, 11=> Fast PWM(WGM01:00)
  TCCR2B = 0b00001010;  //00=> utiliser pour mode non pwm (FOC2A:FOC2B), 00=> reserver, 1=> Fast PWM(WGM02), 010=> diviseur de 8 pour la clock (CS00:01:02)

  OCR2A = 38;  //valeur max du comparateur
  OCR2B = 15;  //valeur a comparer (duty cycle 0 to OCR2A)
  sei();       // Active l'interruption globale
}

void MPPT(float tension, float courant, float *pInst, float *pPrec, int *PWM){
  *pInst  = tension * courant;  //calcul de la puissance instantannee

  if (*pInst > *pPrec){
    //augmentation du PWM
    *PWM = *PWM + 1;
    if(*PWM > 90){
      *PWM = 90;
    }
  }
  else  //dimionution du PWM
  {
    *PWM = *PWM - 1;
    if(*PWM < 10){
      *PWM = 10;
    } 
  }

  *pPrec = *pInst;  //mise a jour de la puissance precedente
}