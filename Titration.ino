// The Titration Machine
// (c) Nick DeGroot 2018
// Created for the LOHS AP Chemistry final project.

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
    lcd.begin(16, 2);
    
    // Start LCD print.
    lcd.clear();
    lcd.print("The Titrator");
    delay(2000);
    lcd.clear();
}

void loop() {
  
}
