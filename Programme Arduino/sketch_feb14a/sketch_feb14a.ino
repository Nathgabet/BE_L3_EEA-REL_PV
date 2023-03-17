#define Correction 100    // pourcentage de correction de la sensibilité du capteur
#define Filtre 0          // Filtre=1 si utilisation des filtres du module
#define Echantillon 5000  // nombre d'échantillons
#define CS 10             // affectation de la broche CS

#include <SPI.h>  // appel de la bibliothèque

int MSB;
int LSB;
signed int valeur;
signed int total = 0;
signed int milli_amps;

void setup() {
  Serial.begin(9600);                    // initialisation de la liaison série
  SPI.begin();                           // initialisation du port SPI
  SPI.setDataMode(SPI_MODE0);            // configuration de la liaison SPI en mode 0
  SPI.setClockDivider(SPI_CLOCK_DIV16);  // configuration de l'horloge à 1MHz
  pinMode(CS, OUTPUT);
}

void loop() {
  if (Filtre == 1) {
    for (int i; i < Echantillon; i++) {
      digitalWrite(CS, LOW);                                                      // activation de la ligne CS
      MSB = SPI.transfer(0x00);                                                   // récupération des bit de poids forts
      LSB = SPI.transfer(0x00);                                                   // récupération des bit de poids faibles
      digitalWrite(CS, HIGH);                                                     // désactivation de la ligne CS
      valeur = (Correction / 100) * (10000 * (((MSB << 8) | LSB) - 2048)) / 899;  //formule donnée dans la documentation
      total = total + valeur;
    }
    milli_amps = total / Echantillon;
  } else {
    digitalWrite(CS, LOW);                                                          // activation de la ligne CS
    MSB = SPI.transfer(0x00);                                                       // récupération des bit de poids forts
    LSB = SPI.transfer(0x00);                                                       // récupération des bit de poids faibles
    digitalWrite(CS, HIGH);                                                         // désactivation de la ligne CS
    milli_amps = (Correction / 100) * (10000 * (((MSB << 8) | LSB) - 2048)) / 899;  //formule donnée dans la documentation
  }
  Serial.print("Courant=");
  Serial.print(milli_amps);
  Serial.println(" mA");
  delay(500);
}
