#include "motor.h"
#include "Arduino.h"

Motor::Motor(int motorID){
    Serial.println("motor init");
    this->motorID = motorID;
}

void Motor::update(unsigned long currentTime){
    // Serial.print(this->stepsLeft);
    // Serial.println(" steps left to do");
    if(this->stepsLeft > 0 && (currentTime - this->lastStep >= this->stepDelay)){
        this->currentStep++;
        this->stepsLeft--;
        this->lastStep = currentTime;
    }
}

void Motor::setRotation(int steps){
    this->stepsLeft = steps;
}

// used by the motor controller
bool Motor::getCurrentStep(int pos){
    return this->steps[this->currentStep%4][pos];
}