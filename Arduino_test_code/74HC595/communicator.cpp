#include <Arduino.h>
#include "communicator.h"

Communicator::Communicator(){
    // esp initializitaion

    //Serial initialization
}

// triggered every programm cycle
void Communicator::update(){
    // perhaps a keepalive ping or whatever
}

// triggered on a job change
void Communicator::newJob(){

}

// update the unity app over serial comm
void Communicator::updateUnity(byte jobID){

}

// Update the other esp
void Communicator::updateRing(byte jobID){

}