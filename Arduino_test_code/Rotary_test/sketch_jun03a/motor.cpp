#include "motor.h"
#include "Arduino.h"

Motor::Motor(int _motorPin1, int _motorPin3, int _motorPin2, int _motorPin4){
    Serial.println("motor init");

    this->motorPin1 = _motorPin1;
    this->motorPin2 = _motorPin2;
    this->motorPin3 = _motorPin3;
    this->motorPin4 = _motorPin4;


    pinMode(this->motorPin1, OUTPUT);
    pinMode(this->motorPin2, OUTPUT);
    pinMode(this->motorPin3, OUTPUT);
    pinMode(this->motorPin4, OUTPUT);

    this->stepDelay = 60L * 1000L * 1000L / 1024 / 10;
}

void Motor::update(){
    if(this->stepsLeft > 0){
        unsigned long noww = micros();
        if(noww - this->lastStep >= this->stepDelay){
            this->currentStep++;
            this->stepsLeft--;
            this->lastStep = noww;
            stepM(this->currentStep % 4);
        }
    }
}

void Motor::setRotation(int rot){
    this->stepsLeft = rot;
}

void Motor::stepM(int stepC){
    switch(stepC){
        case 0:  // 1010
            digitalWrite(this->motorPin1, HIGH);
            digitalWrite(this->motorPin2, LOW);
            digitalWrite(this->motorPin3, HIGH);
            digitalWrite(this->motorPin4, LOW);
        break;
        case 1:  // 0110
            digitalWrite(this->motorPin1, LOW);
            digitalWrite(this->motorPin2, HIGH);
            digitalWrite(this->motorPin3, HIGH);
            digitalWrite(this->motorPin4, LOW);
        break;
        case 2:  //0101
            digitalWrite(this->motorPin1, LOW);
            digitalWrite(this->motorPin2, HIGH);
            digitalWrite(this->motorPin3, LOW);
            digitalWrite(this->motorPin4, HIGH);
        break;
        case 3:  //1001
            digitalWrite(this->motorPin1, HIGH);
            digitalWrite(this->motorPin2, LOW);
            digitalWrite(this->motorPin3, LOW);
            digitalWrite(this->motorPin4, HIGH);
        break;
    }
}
