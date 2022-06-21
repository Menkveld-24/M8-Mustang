#include "motor.h"
#include "Arduino.h"

Motor::Motor(int motorID){
    Serial.println("motor init");
    this->motorID = motorID;
}

// update the motor position 
void Motor::update(unsigned long currentTime){
    // If we have steps left and waited long enough, step!
    if(this->stepsLeft > 0 && (currentTime - this->lastStep >= this->stepDelay)){
        // Checking rotation
        if(this->rotateClockWise){
            this->currentStep++;
            this->stepsLeft--;
        } else {
            this->currentStep--;
            this->stepsLeft++;
        }
        this->lastStep = currentTime;

        // Step number clipping
        if(this->currentStep == 0) this->currentStep = STEPCOUNT;
        else if(this->currentStep == STEPCOUNT) this->currentStep = 0;
    }
}

// adding the amount of steps it needs to '-' is counterclockwise
void Motor::setRotation(int steps){
    this->stepsLeft = steps;
    if(this->stepsLeft > 0) this->rotateClockWise = true;
    else this->rotateClockWise = false;
}

// used by the motor controller to get the current step
bool Motor::getCurrentStep(int pos){
    return this->steps[this->currentStep%4][pos];
}

// we are not moving
bool Motor::isIdle(){
    return this->stepsLeft == 0;
}