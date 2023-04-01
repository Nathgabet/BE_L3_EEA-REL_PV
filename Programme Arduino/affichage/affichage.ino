#include <Wire.h>
#include "rgb_lcd.h"



rgb_lcd lcd;
int Tension = A0;
int In;
int Courant= 6;

void setup() {

lcd.begin(16,2);

}

void loop() {
  // put your main code here, to run repeatedly:
 In = (analogRead(Tension))*0.005;
 aff_I(In,Courant);
 delay(100);
}


void aff_I(int tension, int courant){
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Vpv:");
lcd.setCursor(4,0);
lcd.print(tension*4.8);
lcd.setCursor(0,1);
lcd.print("Ipv:");
lcd.setCursor(4,1);
lcd.print(courant);
}