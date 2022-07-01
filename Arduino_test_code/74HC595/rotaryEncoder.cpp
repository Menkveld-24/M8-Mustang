#include "rotaryEncoder.h"
#include <Arduino.h>

int test = 0;

RotaryEncoder::RotaryEncoder(){
    pinMode(PINA, INPUT);
    pinMode(PINB, INPUT);
    // digitalWrite(PINA, HIGH);
    // digitalWrite(PINB, HIGH);
    this->previousStateA = digitalRead(PINA);
    this->previousStateB = digitalRead(PINB);

    for(int i = 0; i < 50; i++){
        this->previousPositions.push_back(0);
    }
}

void RotaryEncoder::update(){
    if(micros() - this->lastMeasure >= SAMPLING_DELAY) {
        bool readA = digitalRead(PINA);
        bool readB = digitalRead(PINB);
        this->lastMeasure = micros();

        // prev AB -> AB
        // 00 -> 10 -> 11 -> 01 -> 00     
        // 00 -> 01 -> 11 -> 10 -> 00
        // 00 -> 01 to right
        // 00 -> 10 left
        // 01 -> 11 right
        // 01 -> 00 left
        // 11 -> 10 right
        // 11 -> 01 left
        // 10 -> 11 right
        // 10 -> 00 left
        if((!this->previousStateA && !this->previousStateB && readA && !readB) //00 -> 10 right
            || (!this->previousStateA && this->previousStateB && !readA && !readB) //01 -> 00
            || (this->previousStateA && this->previousStateB && !readA && readB) //11 -> 01
            || (this->previousStateA && !this->previousStateB && readA && readB)){ //10 -> 11
                this->position--; //to right
        } else if ((!this->previousStateA && !this->previousStateB && !readA && readB) // 00-> 01
            || (!this->previousStateA && this->previousStateB && readA && readB) //01 -> 11
            || (this->previousStateA && this->previousStateB && readA && !readB) //11 -> 10
            || (this->previousStateA && !this->previousStateB && !readA && !readB)){ //10 -> 00
                this->position++;
        }
        if(this->position < 0) this->position = (JOBCOUNT+1)*STEPS_PER_ROTATION;
        else if(this->position > (1+JOBCOUNT)*STEPS_PER_ROTATION) this->position = 0;
        this->previousStateA = !readA;
        this->previousStateB = !readB;
    }
}

// Converting the step position to a job number
int RotaryEncoder::getCurrentJobID(){
    int currentPosition = abs(this->position);
    // if(this->position < 0) currentPosition += JOBCOUNT*STEPS_PER_ROTATION;
    // currentPosition = currentPosition%(JOBCOUNT*STEPS_PER_ROTATION);
    // // Serial.print(currentPosition);
    // // Serial.print(" : ");
    byte currentjob = map(currentPosition, 0, (JOBCOUNT+1)*STEPS_PER_ROTATION, 0, JOBCOUNT);
    if(currentjob == 30) currentjob = 0;
    this->previousPositions.push_front(currentjob);
    this->previousPositions.pop_back();

    std::unordered_map<int, int> frequencies;
    for(int i = 0; i < this->previousPositions.size(); i++){
        frequencies[this->previousPositions[i]]++;
    }
    byte mostFrequent = -1;
    byte maxCount = 0;
    for(int i = 0; i < frequencies.size(); i++){
        // // Serial.print(i);
        // // Serial.println(frequencies[i]);
        if(frequencies[i] > maxCount){
            maxCount = frequencies[i];
            mostFrequent = i;
        }
    }

    return mostFrequent;
}

// Calling this function after update, it returns -1 if the previous loop had the same job (no change)
// or it returns the job id 
int RotaryEncoder::listenForJobChange(){
    byte lastJob = this->previousJob;
    byte currentJob = this->getCurrentJobID();
    this->previousJob = currentJob;
    // // Serial.print(lastJob);
    // // Serial.println(currentJob);
    if(lastJob != currentJob){
        // Serial.print(this->position);
        // Serial.print(this->getCurrentJobID());
        // Serial.println(this->previousJob);
        return currentJob;
    }
    return -1;
}