#include <SPI.h>  // appel de la bibliothèque

#define CS 10             // affectation de la broche CS

int MSB;// initialise MSB pour bit de poids forts 
int LSB;// initialise LSB bit de poid faible
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

  digitalWrite(CS, LOW);     // activation de la ligne CS
  MSB = SPI.transfer(0x00);  // récupération des bit de poids forts
  LSB = SPI.transfer(0x00);  // récupération des bit de poids faibles
  digitalWrite(CS, HIGH);    // désactivation de la ligne CS

  milli_amps = 1.1335 * (1000 / 89.95) * (((MSB << 8) | LSB) - 2048);// formule de la datasheet * la valeur de correction
  Serial.print("Courant="); //
  Serial.print(milli_amps);
  Serial.println(" mA");
  delay(500);
}
