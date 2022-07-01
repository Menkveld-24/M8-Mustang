#include "motorController.h"
#include "rotaryEncoder.h"
#include "communicator.h"
#include "transitionManager.h"
// Main program can keep the program state
// 

MotorController controller;
RotaryEncoder encoder;
Communicator communicator;
TransitionManager transitionManager;

bool alreadyTransitioning = false;
unsigned long lastPressed;
bool buttonPressed = false;

#define BUTTON_PIN 5
#define RESET_DELAY 3000
#define RESET -1

//switch is pin 5

void setup(){
    Serial.begin(9600);
    communicator.initESP();
    // Serial.print("Started program!");
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    Serial.flush();
    communicator.updateRing(RESET, 0);
}


void loop(){
    controller.update();
    encoder.update();
    communicator.update();
    transitionManager.update();

    checkForJobUpdates();

    if(transitionManager.canReturnToIdle()) controller.returnAllToIdle();

    //allow serial input to select a job
    // while(// Serial.available() > 0){
    //     byte currentJob = // Serial.parseInt();
    //     // Serial.print("Received: ");
    //     // Serial.println(currentJob);
        
    //     byte nextLevel = transitionManager.selectButtonPressed(currentJob);
    //     if(nextLevel == STILL_TRANSITIONING) {
    //         // Serial.println("Still busy");
    //         return;
    //     };
    
    //     controller.newJobSelected(currentJob, nextLevel);
    //     communicator.newJobSelected(currentJob, nextLevel);
    //     // Serial.println(millis());
    // }

    if(!buttonPressed && !digitalRead(BUTTON_PIN)) selectButtonPressed();
    if(buttonPressed && digitalRead(BUTTON_PIN)) selectButtonReleased();
}

// // check jor updates on the rotary encoder and relay this to the ring
void checkForJobUpdates(){
    int jobChange = encoder.listenForJobChange();
    if(jobChange == -1) return;

    // Serial.print("Rotated to a new job: ");
    // Serial.println(jobChange);
    communicator.newJob(jobChange);
}

//large big button is pressed to select a job
void selectButtonPressed(){
    byte currentJob = encoder.getCurrentJobID();
    byte nextLevel = transitionManager.selectButtonPressed(currentJob);
    if(nextLevel == STILL_TRANSITIONING) return;

    lastPressed = millis();
    buttonPressed = true;
    // Serial.println("Pressed button");
    
    controller.newJobSelected(currentJob, nextLevel);
    communicator.newJobSelected(currentJob, nextLevel);
}

void selectButtonReleased(){
    buttonPressed = false;
    // Serial.println("Button released");
    // Serial.print(millis() - lastPressed);
    //button released after RESET_DELAY
    if(millis() - lastPressed > RESET_DELAY){
        // Serial.println("Reset!");
        communicator.updateRing(RESET, 0);
        controller.returnAllToIdle();
        digitalWrite(BUTTON_LED, HIGH);
        delay(20);
        digitalWrite(BUTTON_LED, LOW);
    }
}
