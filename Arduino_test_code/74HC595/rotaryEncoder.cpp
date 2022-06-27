#include "rotaryEncoder.h"
#include <Arduino.h>

#define STEPS_PER_ROTATION 4000
#define JOBCOUNT 30
#define PINA 22
#define PINB 23

RotaryEncoder::RotaryEncoder(){
    // digitalWrite(PINA, HIGH);
    // digitalWrite(PINB, HIGH);
    pinMode(PINA, INPUT);
    pinMode(PINB, INPUT);
    this->previousStateA = digitalRead(PINA);
    this->previousStateB = digitalRead(PINB);
}

void RotaryEncoder::update(){
    bool readA = digitalRead(PINA);
    bool readB = digitalRead(PINB);
    // Serial.print(readA);
    // Serial.println(readA == this->previousStateA);
    if(readA != this->previousStateA || readB != this->previousStateB){
        if ((readA==1 && this->previousStateA==0 && readB==0) || (readA==0 && this->previousStateA==1 && readB==1) || (readB==1 && this->previousStateB==0 && readA==1) || (readB==0 && this->previousStateB==1 && readA==0)) this->position++;
        else if ((readB==1 && this->previousStateB==0 && readA==0) || (readB==0 && this->previousStateB==1 && readA==1) || (readA==1 && this->previousStateA==0 && readB==1) || (readA==0 && this->previousStateA==1 && readB==0)) this->position--;
        Serial.println(this->position);
    }
    this->previousStateA = readA;
    this->previousStateB = readB;
    
    // position clipping
    // if(this->position == 0) this->position = STEPS_PER_ROTATION;
    // else if(this->position == STEPS_PER_ROTATION) this->position = 0;
}

// Converting the step position to a job number
int RotaryEncoder::getCurrentJobID(){
    this->position = map(this->position, 0, STEPS_PER_ROTATION, 0, JOBCOUNT)
    return this->position;
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