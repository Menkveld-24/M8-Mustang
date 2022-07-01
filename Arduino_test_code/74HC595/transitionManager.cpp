#include <Arduino.h>
#include "transitionManager.h"

TransitionManager::TransitionManager(){
    pinMode(BUTTON_LED, OUTPUT);
    digitalWrite(15, HIGH);
}

void TransitionManager::update(){
    if(!this->alreadyTransitioning) return;

    if(millis() - this->timeSinceLastButtonPress >= ((TransitionManager::getAnimationDuration(this->currentStressLevel)*1000)+ (FADE_OUT_DELAY*1000))){
        this->alreadyTransitioning = false;
        digitalWrite(BUTTON_LED, HIGH);
        // Serial.println(millis());
        // Serial.println("Re-enabled");
    }
}

byte TransitionManager::selectButtonPressed(byte currentJob){
    if(this->alreadyTransitioning) return STILL_TRANSITIONING;

    digitalWrite(BUTTON_LED, LOW);
    //get the next stress state we want to go to
    byte nextState = this->jobStressLevel[currentJob];
    this->currentStressLevel = nextState;
    this->timeSinceLastButtonPress = millis();
    this->alreadyTransitioning = true;
    this->alreadyToIdle = false;
    return nextState;
}

// convert a stress level to a duration for the transition from idle to stress level
byte TransitionManager::getMotorDuration(byte stressLevel){
    return TransitionManager::motorDelays[stressLevel];
}

byte TransitionManager::getAnimationDuration(byte stressLevel) {
    return TransitionManager::transitionDelays[stressLevel];
}

bool TransitionManager::canReturnToIdle(){
    if(this->alreadyToIdle) return false;
    if(this->alreadyTransitioning && (millis() - this->timeSinceLastButtonPress >= (TransitionManager::getAnimationDuration(this->currentStressLevel)*1000))){
        // Serial.println("Motors can go down again!");
        this->alreadyToIdle = true;
        return true;
    }
    return false;
}