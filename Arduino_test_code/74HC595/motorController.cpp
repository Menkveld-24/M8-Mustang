#include "motor.h"
#include "motorController.h"
#include "Arduino.h"

MotorController::MotorController(){
    // Setting the shift register pins
    pinMode(MotorController::latchPin, OUTPUT);
    pinMode(MotorController::clockPin, OUTPUT);
    pinMode(MotorController::dataPin, OUTPUT);

    for(int i = 0; i < MotorController::motorCount; i++){
        this->motors[i].setRotation(-STEPCOUNT*5);
    }

    Serial.println("MotorController initialized");
}

void MotorController::update(){
    unsigned long now = micros();
    for(int i = 0; i < MotorController::motorCount; i++){
        this->motors[i].update(now);
    };

    // This section is all about preparing the bits for the shift registers
    // For each motor it collects the high/low as a boolean and writes that on an 8-bit
    // position somewhere on the shiftData array
    // this function works from reverse to front so it does the last motor first, this is also
    // the first data to send out, the shiftOut function has only support for bytes, hence there
    // is no one long row of bits
    int lastBit = -1;
    //odd motor number, start at 0000
    if(this->motorCount%2 == 1){
        lastBit = 3;
    }
    
    // creating a data array to send out in bytes, set all to 00000000
    byte shiftData[(this->motorCount+1)/2] = { 0b00000000 };
    std::fill(shiftData, shiftData+((this->motorCount+1)/2), 0b00000000);

    byte currentShift = 0;
    // Loop per step per motor and append that to the shiftData
    for(int i = MotorController::motorCount-1; i >= 0; i--){
        for(int j = 0; j < 4; j++){
            lastBit++;
            bitWrite(shiftData[currentShift], lastBit, this->motors[i].getCurrentStep(j));
            // We have filled this byte, move to next
            if(lastBit == 7){
                lastBit = -1;
                currentShift++;
            }
        };
    };

    // Shift register write action
    digitalWrite(17, LOW);
    for(int i = 0; i < (this->motorCount+1)/2; i++){
        shiftOut(4, 16, LSBFIRST, shiftData[i]);
    }
    digitalWrite(17, HIGH);
}

void MotorController::setSteps(int motorID, int stepCount){
    if(motorID < 0 || motorID > MotorController::motorCount) return;
    
    this->motors[motorID].setRotation(stepCount);
}