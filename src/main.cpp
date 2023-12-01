#include <Arduino.h>
#include <EEPROM.h>
#include <Stepper.h>

int stepperMode; // Defines if the motor is active or inactive
const int stepsPerRevolution = 1024; // Number of steps
Stepper myStepper = Stepper(stepsPerRevolution, 9, 10, 11, 8);

void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(10); // Sets the motor's speed

  stepperMode = EEPROM.read(0);
  if(stepperMode != 0 && stepperMode != 1) {

    // The first power cycle is detected when the EEPROM value is different
    // from 0 or 1.
    EEPROM.update(0, 1);
    stepperMode = 1;
  }

  if(stepperMode == 0) {
    
    // During the last power cycle, the stepper was inactive
    // we want it to be active now.
    EEPROM.update(0, 1);

  } else if(stepperMode == 1) {
    
    // During the last power cycle, the stepper was active
    // we want it to be inactive now.
    EEPROM.update(0, 1);
  }


}

void loop() {
  if(stepperMode == 1) {
    Serial.println("TURNED ON");
    myStepper.step(stepsPerRevolution);
    myStepper.step(-stepsPerRevolution);
  }
}