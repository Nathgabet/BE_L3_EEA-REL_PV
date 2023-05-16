#include "DHT.h"
#include <Wire.h>
#include <SPI.h>  // appel de la bibliothèque
#include "rgb_lcd.h"

#define DHTPIN 5     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
rgb_lcd lcd;

void setup() {
  Serial.begin(9600);
   lcd.begin(16, 2);
   dht.begin();
}

void loop() {

  float t = dht.readTemperature();

  affiche_text("Temp : ", 0, 0, 1);
  affiche_variable(t, 7, 0);
  affiche_text(" C", 13, 0, 0);

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