#include "motor.h"
#include "Arduino.h"

Motor::Motor(byte motorID, byte switchPin, int maxHeight){
    // Serial.println("motor init");
    this->motorID = motorID;
    this->switchPin = switchPin;
    this->maxHeight = maxHeight;

    pinMode(this->switchPin, INPUT);
}

// update the motor position 
void Motor::update(unsigned long currentTime){
    // If we have steps left and waited long enough, step!
    if(this->stepsLeft != 0 && (currentTime - this->lastStep >= this->stepDelay)){
        // Checking rotation
        if(this->moveUpwards){
            this->currentStep++;
            this->stepsLeft--;
        } else {
            this->currentStep--;
            this->stepsLeft++;
            // if(this->motorID == 0){
            //     // Serial.println(this->stepsLeft);
            // }
        }
        this->lastStep = currentTime;

        // Step number clipping
        // if(this->currentStep == 0) this->currentStep = STEPCOUNT;
        // else if(this->currentStep == STEPCOUNT) this->currentStep = 0;

        // when we hit the switch, set our position back to 0
        if((digitalRead(this->switchPin) || this->stepsLeft == 0) && !this->moveUpwards){
            // Serial.print("Motor hit bottom! :");
            // Serial.print(this->motorID);
            // Serial.print(" reading: ");
            // Serial.println(digitalRead(this->switchPin));
            stepsLeft = 0;
            this->currentStep = 0;
        }
    }
}

// adding the amount of steps it needs to '-' is counterclockwise
void Motor::setRotation(int steps){
    // we request more steps than we can 
    // if(steps > this->maxHeight-this->currentStep){
    //     this->stepsLeft = this->maxHeight-this->currentStep; 
    //     this->moveUpwards =  true;  
    //     // we request negative steps
    if(steps < 0){
        this->moveUpwards = false;
    } else {
        this->moveUpwards =  true;
    }
    this->stepsLeft = steps;
    // if(this->stepsLeft > 0) this->moveUpwards = true;
    // else this->moveUpwards = false;
}

// used by the motor controller to get the current step
bool Motor::getCurrentStep(int pos){
    if(this->stepsLeft == 0) return false;
    return this->steps[this->currentStep%4][pos];
}

// we are not moving
bool Motor::isIdle(){
    return this->stepsLeft == 0;
}

// retract the motor entirely
void Motor::returnToHome(){
    // Serial.print("Motor to home: ");
    // Serial.println(this->motorID);
    setRotation(-this->maxHeight);
}

// fully push out the motor
void Motor::extendToTop(){
    // // Serial.println(this->currentStep);
    if(this->currentStep >= this->maxHeight) {
        // Serial.print("Motor already at top");
        return;
    }
    // Serial.print("Motor to top: ");
    // // Serial.println(this->motorID);
    setRotation(this->maxHeight);
}

void Motor::extendToHalf(){
    // Serial.print("Motor to half: ");
    // Serial.println(this->motorID);
    setRotation(static_cast <byte> (this->maxHeight/2));
}

// NOT CORRECT YET
//Create new delay for the motor
void Motor::updateMotorDelay(byte transitionDuration){
    if(this->stepsLeft == 0) return;
    // Serial.print("Motor: ");
    // Serial.println(this->motorID);

    // Serial.print("Steps left: ");
    // Serial.println(this->stepsLeft);
    
    // this->stepDelay = 1000L * 1000L / STEPCOUNT / (abs(this->stepsLeft) / transitionDuration);
    this->stepDelay = ((transitionDuration * 1000 * 1000) / abs(this->stepsLeft)); //nr of steps / time in sec = steps/sec / steps/sec *1000 = steps/msec, 

    // Serial.print("New delay: ");
    // Serial.println(this->stepDelay);
    // Serial.print("Steps * delay: ");
    // Serial.println(this->stepDelay * abs(this->stepsLeft));
}