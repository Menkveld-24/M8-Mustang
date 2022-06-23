#include "motor.h"
#include "Arduino.h"

Motor::Motor(byte motorID, byte switchPin, int maxHeight){
    Serial.println("motor init");
    this->motorID = motorID;
    this->switchPin = switchPin;
    this->maxHeight = maxHeight;

    pinMode(this->switchPin, INPUT);
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

        // when we hit the switch, set our position back to 0
        if(digitalRead(this->switchPin)){
            stepsLeft = 0;
        }
    }
}

// adding the amount of steps it needs to '-' is counterclockwise
void Motor::setRotation(int steps){
    if(steps > this->maxHeight-this->currentStep){
        this->stepsLeft = this->maxHeight-this->currentStep;    
    } else {
        this->stepsLeft = steps;
    }
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

// retract the motor entirely
void Motor::returnToHome(){
    setRotation(-this->maxHeight);
}

// fully push out the motor
void Motor::extendToTop(){
    setRotation(this->maxHeight);
}