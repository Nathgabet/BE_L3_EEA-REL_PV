#include <Wire.h>
#include <SPI.h>  // appel de la bibliothèque
#include "rgb_lcd.h"

#define CS 10  // affectation de la broche CS
rgb_lcd lcd;

int Tension = A0;
int tension;

float courant ;
int MSB;  // initialise MSB pour bit de poids forts
int LSB;  // initialise LSB bit de poid faible

float pInst =0;
float pPrec =0;

int PWM =10;

void setup() {
  Serial.begin(9600);
  initTimer2(); //initialisation du timer2
  
  SPI.begin();                           // initialisation du port SPI
  SPI.setDataMode(SPI_MODE0);            // configuration de la liaison SPI en mode 0
  SPI.setClockDivider(SPI_CLOCK_DIV64);  // configuration de l'horloge à 1MHz
  pinMode(CS, OUTPUT);

  lcd.begin(16, 2);
}

void loop() {
  courant = Courant(); //lecture du courant
  tension = ((analogRead(Tension)) * 0.0048) / 0.227;

  affiche_text("Ipv:", 0, 0, 1);
  affiche_variable(courant, 4, 0);

  affiche_text("Upv:", 0, 1, 0);
  affiche_variable(tension, 4, 1);
  
  MPPT(tension, courant, &pInst, &pPrec, &PWM); //recherche du point MPPT
  OCR2B = (OCR2A / 100.0) *PWM; //modification du PWM de sortie
  delay(3000);

  affiche_text("Ppv:", 0, 0, 1);
  affiche_variable(pPrec, 4, 0);
  delay(3000);
}

float Courant(){
  signed int milli_amps;
  digitalWrite(CS, LOW);                                      // activation de la ligne CS
  MSB = SPI.transfer(0x00);                                   // récupération des bit de poids forts
  LSB = SPI.transfer(0x00);                                   // récupération des bit de poids faibles
  digitalWrite(CS, HIGH);                                     // désactivation de la ligne CS
  milli_amps = ((1000 / 89.95) * (((MSB << 8) | LSB) - 2048))/1000;  // formule de la datasheet * la valeur de correction
  
  return milli_amps;
}

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
  else  //diminution du PWM
  {
    *PWM = *PWM - 1;
    if(*PWM < 10){
      *PWM = 10;
    } 
  }

  *pPrec = *pInst;  //mise a jour de la puissance precedente
}

void affiche_text(const char *texte, int curseur, int ligne, int clear) {
  if (clear)
    lcd.clear();                                                                // on efface ce qui est récrit sur l'afficheur
  lcd.setCursor(curseur, ligne);                                               // on décale le curseur de 5cases pour afficher la tension
  lcd.print(texte);                                                            //on affiche Upot pout tension du potentiometre
}

void affiche_variable(float variable, int curseur, int ligne) {                                               // on efface ce qui est récrit sur l'afficheur
  lcd.setCursor(curseur, ligne);                                                                              // on décale le curseur de 5cases pour afficher la tension
  lcd.print(variable);
}