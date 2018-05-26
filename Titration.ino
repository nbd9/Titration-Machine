// The Titration Machine
// (c) Nick DeGroot 2018
// Created for the LOHS AP Chemistry final project.
// Hardcoded for HCl + NaOH --> H2O + NaCl, or any 1:1 acid base ratio

#include "VernierLib.h"
VernierLib Vernier;

// ACID BASE VALUES
// CHANGE THESE BASED ON EXPERIMENT
const float mlAcid = 50.0;
const float molarBase = 0.1;
const float mlPerDrop = 0.045;
const float dropOffset = 10.0;

// Global Values
float mlBase = mlPerDrop * (-1.0 * dropOffset);
float molarAcid = 0.0;
float pH = 0.0;
bool gateFlipped = false;
float highestDeriv = 0.0;
float mlBaseForNeutralization = 0.0;

void setup() {
  Vernier.autoID();
  pH = Vernier.readSensor();
  
  Serial.begin(9600);
  Serial.print("Initial pH: ")
  Serial.println(pH);
}
 
void loop() {
  float sensorPh = Vernier.readSensor(); // Getting pH

  int photogate = digitalRead(2); // Low when blocked
  if (photogate == LOW) {
    if (!gateFlipped) {
      gateFlipped = true;
      mlBase += mlPerDrop;

      float firstDeriv = (sensorPh - pH) / mlPerDrop;
      Serial.println(firstDeriv);
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

      // Printing update to serial and LCD
      Serial.print("pH: ");
      Serial.print(pH, 5); // 5 Sig Figs
      Serial.print("\tmL of Base: ");
      Serial.print(mlBase);
      Serial.print("\tPredicted acid molarity: ");
      Serial.println(molarAcid, 5); // 5 Sig Figs
    }
 } else {
   gateFlipped = false;
 }
}

