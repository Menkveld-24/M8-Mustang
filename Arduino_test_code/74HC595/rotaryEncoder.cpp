#include "rotaryEncoder.h"
#include <Arduino.h>

#define STEPS_PER_ROTATION 4000
#define JOBCOUNT
#define PINA 6
#define PINB 6

RotaryEncoder::RotaryEncoder(){
    pinMode(PINA, INPUT);
    pinMode(PINB, INPUT);
}

void RotaryEncoder::update(){
    bool aState = digitalRead(PINA);
    if(aState != this->previousState){
        if(digitalRead(PINB) != aState) this->position++;
        else this->position--;
    }
    this->previousState = aState;
    
    // position clipping
    if(this->position == 0) this->position = STEPS_PER_ROTATION
    else if(this->position == STEPS_PER_ROTATION) this->position = 0;
}

// Converting the step position to a job number
int RotaryEncoder::getCurrentJobID(){
    return this->position%JOBCOUNT;
}

// Calling this function after update, it returns -1 if the previous loop had the same job (no change)
// or it returns the job id 
int RotaryEncoder::listenForJobChange(){
    byte lastJob = this->previousJob;
    byte currentJob = this->getCurrentJobID();
    this->previousJob = currentJob;
    if(lastJob != currentJob) return currentJob;
    return -1;
}