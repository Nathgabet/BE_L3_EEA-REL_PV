#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

void setup() {
lcd.begin(16,2);
}

void loop() {
lcd.setCursor(0,0);
lcd.print("Vpv:");
lcd.setCursor(4,0);
lcd.print(variable);
lcd.clear();
}




int Tension = A0;
int In;
int Courant= 6;

  // put your main code here, to run repeatedly:
 
 aff_I(In,Courant);
 delay(100);