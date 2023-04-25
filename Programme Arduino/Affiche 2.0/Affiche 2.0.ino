#include <Wire.h>
#include <SPI.h>  // appel de la bibliothèque
#include "rgb_lcd.h"

#define CS 10  // affectation de la broche CS
rgb_lcd lcd;

int Tension = A0;
int tension;
int MSB;  // initialise MSB pour bit de poids forts
int LSB;  // initialise LSB bit de poid faible
signed int milli_amps;

void setup() {
  Serial.begin(9600);                    // initialisation de la liaison série
  SPI.begin();                           // initialisation du port SPI
  SPI.setDataMode(SPI_MODE0);            // configuration de la liaison SPI en mode 0
  SPI.setClockDivider(SPI_CLOCK_DIV64);  // configuration de l'horloge à 1MHz
  pinMode(CS, OUTPUT);

  lcd.begin(16, 2);
}

void loop() {

  digitalWrite(CS, LOW);                                      // activation de la ligne CS
  MSB = SPI.transfer(0x00);                                   // récupération des bit de poids forts
  LSB = SPI.transfer(0x00);                                   // récupération des bit de poids faibles
  digitalWrite(CS, HIGH);                                     // désactivation de la ligne CS
  milli_amps = (1000 / 89.95) * (((MSB << 8) | LSB) - 2048);  // formule de la datasheet * la valeur de correction
  
    // on enregistre le valuer lu sur le pin A0 dans tension
  affiche_text("Ipv:", 0, 0, 1);
  affiche_variable(milli_amps, 4, 0);
  
tension = analogRead(Tension);
  affiche_text("Upv:", 0, 1, 0);
  affiche_variable((tension * 0.0048) / 0.227, 4, 1);
  delay(1000);
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



