// The Titration Machine
// (c) Nick DeGroot 2018
// Created for the LOHS AP Chemistry final project.

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// LINEAR CALIBRATION VALUES
const float slope = -3.838;
const float intercept = 13.720;
const String units = " pH";

// ACID BASE VALUES
// Constants
const int pKw = 14;

// Constant Acid -- HCl
const float mLAcid = 25.dob0;
const float MAcid = 0.1;
// Changing base
float mLbase = 0;
float MBase = 0;

float firstDir = 0;
float secondDir = 0;

// 20 DROPS = 1 ML //
 
void setup() {
  lcd.begin(16, 2);

  // Start LCD print.
  lcd.clear();
  lcd.print("The Titrator");
  delay(2000);
  lcd.clear();

  Serial.begin(9600); //setup communication to display
}
 
void loop() {
  float rawCount = analogRead(A0); //read one data value (0-1023)
  float voltage=rawCount/1023*5; //convert raw count to voltage (0-5V)
  float pH = slope * voltage + intercept; //convert to sensor value with linear calibration equation
  Serial.print(pH);
  delay(500); //wait half second
}

