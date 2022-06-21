#ifndef _MOTOR_H_
#define _MOTOR_H_

//superclass
#include <Arduino.h>

class Motor{
  public:
    Motor(int _motorPin1, int _motorPin3, int _motorPin2, int _motorPin4);
    void update();
    void setRotation(int rot);
    void stepM(int stepC);
    // void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus);
    

  private:
    int currentStep = 0;
    unsigned long stepDelay;
    unsigned long lastStep;
    int stepsLeft = 0;
    bool rotateClockWise = true;

    int motorPin1;
    int motorPin2;
    int motorPin3;
    int motorPin4;
};

#endif
