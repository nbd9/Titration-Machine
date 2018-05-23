// The Titration Machine
// (c) Nick DeGroot 2018
// Created for the LOHS AP Chemistry final project.
// Hardcoded for HCl + NaOH --> H2O + NaCl, or any 1:1 acid base ratio

#include <LiquidCrystal.h>
#include "VernierLib.h"
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
VernierLib Vernier;

// ACID BASE VALUES
// Constants
const int pKw = 14;
const float mlAcid = 25.0;
const float molarBase = 0.1;

// Global Values
float mlBase = 0.0; // 20 DROPS = 1 mL
float molarAcid = 0.0;
float pH = 0.0;
bool gateFlipped = false;
float highestDeriv = 0.0;
float mlBaseForNeutralization = 0.0;

void setup() {
  Vernier.autoID();
  lcd.begin(16, 2);

  // Start LCD print.
  lcd.clear();
  lcd.print("The Titrator");
  delay(2000);
  lcd.clear();

  Serial.begin(9600);
}
 
void loop() {
  float sensorPh = Vernier.readSensor(); // Getting pH

  int photogate = digitalRead(6); // Low when blocked
  if (photogate == LOW && !gateFlipped) {
    mlBase += 0.05;

    float firstDeriv = (sensorPh - pH) / (0.05);
    if (highestDeriv < firstDeriv) {
      highestDeriv = firstDeriv;
      mlBaseForNeutralization = mlBase;

      // Calculating predicted molarity for current values
      float molBase = (mlBase / 1000) * molarBase;
      float molAcid = molBase;
      molarAcid = molAcid / (mlAcid / 1000);
    }

    // Setting global values
    pH = sensorPh;
    gateFlipped = true;

    // Printing update to serial and LCD
    Serial.print("pH: ");
    Serial.print(pH, 5); // 5 Sig Figs
    Serial.print("\tmL of Base: ");
    Serial.print(mlBase);
    Serial.print("\tPredicted acid molarity: ");
    Serial.println(molarAcid, 5); // 5 Sig Figs
    lcd.setCursor(0, 1);
    lcd.print(mlBase); 
  } else {
    gateFlipped = false;
  }

  lcd.setCursor(0, 0);
  lcd.print(sensorPh, 5); // 5 Sig Figs
}

