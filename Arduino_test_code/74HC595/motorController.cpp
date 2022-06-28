#include "motor.h"
#include "motorController.h"
#include "Arduino.h"
#include <random>

MotorController::MotorController(){
    // Setting the shift register pins
    pinMode(MotorController::latchPin, OUTPUT);
    pinMode(MotorController::clockPin, OUTPUT);
    pinMode(MotorController::dataPin, OUTPUT);

    for(int i = 0; i < MotorController::motorCount; i++){
        this->motors[i].setRotation(-(STEPCOUNT*5));
    }

    // this->motors[0].setRotation(500);
    Serial.println("MotorController initialized");

    // pinMode(12, INPUT);
}

void MotorController::update(){
    unsigned long now = micros();
    for(int i = 0; i < MotorController::motorCount; i++){
        this->motors[i].update(now);
    };

    // if(digitalRead(12)){
    //     for(int i = 0; i < MotorController::motorCount; i++){
    //         this->motors[i].setRotation(100);
    //     };
    // }

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

void MotorController::newJob(byte jobID){
    //check for half
    bool halfTree = this->treeSalaries[jobID]%10 == 5;
    byte treeCount = static_cast<byte>(this->treeSalaries[jobID]/10);
    Serial.print(halfTree);
    Serial.println(treeCount);

    std::vector <byte> allTrees;
    for(int i = 0; i < MotorController::motorCount; i++){
        allTrees.push_back(i);
        // this->motors[i].returnToHome();
    } 
    std::vector <byte> randomTrees;
    // if eleven dont do random
    if(treeCount == 11){
        for(int i = 0; i < allTrees.size(); i++){
            this->motors[i].extendToTop();
        }
        return;
    }

    Serial.print("all trees:");
    Serial.println(allTrees.size());
    srand(micros());
    for(int i = 0; i < treeCount; i++){    
        int randomIndex = rand() % allTrees.size();
        randomTrees.push_back(allTrees[randomIndex]);
        allTrees.erase(allTrees.begin() + randomIndex);
    }

    for(int i = 0; i < randomTrees.size(); i++){
        this->motors[randomTrees[i]].extendToTop();
        Serial.println(randomTrees[i]);
    }

    Serial.print("trees left:");
    Serial.println(allTrees.size());
    Serial.print("random trees:");
    Serial.println(randomTrees.size());
    for(int i = 0; i < allTrees.size(); i++){
        this->motors[allTrees[i]].returnToHome();
    }

    // buggy
    // if(halfTree){        
    //     this->motors[rand() % allTrees.size()].extendToHalf();
    // }
}