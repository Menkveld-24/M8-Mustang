#include "motorController.h"
#include "rotaryEncoder.h"
#include "communicator.h"
// Main program can keep the program state
// 

MotorController controller;
RotaryEncoder encoder;
Communicator communicator;

void setup(){
    Serial.begin(115200);
    communicator.initESP();
    Serial.print("Started program!");
    // attachInterrupt(digitalPinToInterrupt(PINA), rotaryInterruptA, CHANGE);
    // attachInterrupt(digitalPinToInterrupt(PINB), rotaryInterruptB, CHANGE);
}


void loop(){
    controller.update();
    encoder.update();
    communicator.update();

    checkForJobUpdates();
}

// // check jor updates on the rotary encoder and relay this to the ring
void checkForJobUpdates(){
    int jobChange = encoder.listenForJobChange();
    if(jobChange == -1) return;

    Serial.println(jobChange);
    communicator.newJob(jobChange);
    controller.newJob(jobChange);
}

// void rotaryInterruptA(){
//     encoder.interruptA();
// }

// void rotaryInterruptB(){
//     encoder.interruptB();
// }