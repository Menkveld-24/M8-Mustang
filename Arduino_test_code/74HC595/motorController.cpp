#include "motor.h"
#include "motorController.h"
#include "Arduino.h"

MotorController::MotorController(){
    Serial.println("motor init");

    //set pins to output so you can control the shift register
    pinMode(17, OUTPUT);
    pinMode(16, OUTPUT);
    pinMode(4, OUTPUT);

    for(int i = 0; i < MotorController::motorCount; i++){
        // this->motors[]
        Serial.print("New motor");
        this->motors[i].setRotation(500*i+1000);
    }
}

void MotorController::update(){
    unsigned long now = micros();
    for(int i = 0; i < MotorController::motorCount; i++){
        this->motors[i].update(now);
    };

    // prepping data to send out
    // unsigned long shiftData = 0b0;
    int lastBit = 3;
    // float motorz = this->motorCount/2;
    // Serial.println(std::ceil(motorz));
    // TODO CEIL function does not work, rounds 5/2 to 2.00
    byte shiftData[3] = { 0b00000000, 0b00000000, 0b00000000 };
    // if(MotorController::motorCount%2 == 1){
    //     int lastBit = 4;
    // };
    byte currentShift = 0;
    // Serial.println("STARTING WRITING to bytearray");
    for(int i = MotorController::motorCount-1; i >= 0; i--){
        // Serial.print(i);
        // Serial.println(" motor steps:");
        for(int j = 0; j < 4; j++){
            lastBit++;
            // Serial.print(this->motors[i].getCurrentStep(j));
            bitWrite(shiftData[currentShift], lastBit, this->motors[i].getCurrentStep(j));
            if(lastBit == 7){
                lastBit = -1;
                currentShift++;
                // Serial.println("shift");
            }
        };
        // Serial.println("next");
    };

    digitalWrite(17, LOW);
    // CEIL DOES NOT WORK
    for(int i = 0; i < 3; i++){
        shiftOut(4, 16, LSBFIRST, shiftData[i]);
        // Serial.println("s:");
        // Serial.println(shiftData[i], BIN);
    }
    digitalWrite(17, HIGH);
    // delay(400);
}

void MotorController::setSteps(int motorID, int stepCount){
    //
}