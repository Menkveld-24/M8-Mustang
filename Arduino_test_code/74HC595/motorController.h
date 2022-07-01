#ifndef _MOTORCONTROLLER_H_
#define _MOTORCONTROLLER_H_


#include <Arduino.h>
#include "motor.h"

class MotorController{
  public:
    MotorController();
    void update();
    void setSteps(int motorID, int stepCount);
    void newJob(byte jobID);
    void newJobSelected(byte newJobID, byte nextLevel);
    void returnAllToIdle();
    // void getCurrentStep();

    

  private:
    //Pin connected to ST_CP of 74HC595
    static const int latchPin = 17;
    //Pin connected to SH_CP of 74HC595
    static const int clockPin = 16;
    ////Pin connected to DS of 74HC595
    static const int dataPin = 4;

    static const int motorCount = 11;
    // 36, 39, 34, 35, 32, 33, 25, 26, 27, 14, 12
    Motor motors[motorCount] = {
        Motor(0, 39, 1*STEPCOUNT),
        Motor(1, 36, 1*STEPCOUNT),
        Motor(2, 26, 1*STEPCOUNT),
        Motor(3, 33, 1*STEPCOUNT),
        Motor(4, 13, 1*STEPCOUNT),
        Motor(5, 18, 1*STEPCOUNT),
        Motor(6, 35, 1*STEPCOUNT),
        Motor(7, 14, 1*STEPCOUNT),
        Motor(8, 32, 1*STEPCOUNT),
        Motor(9, 27, 1*STEPCOUNT),
        Motor(10, 34, 1*STEPCOUNT),
    };

    const byte treeSalaries[30] = {
        55,
        50,
        20,
        10,
        20,
        25,
        40,
        55,
        10,
        50,
        105,
        60,
        50,
        35,
        80,
        25,
        25,
        110,
        55,
        90,
        15,
        60,
        60,
        25,
        30,
        35,
        35,
        55,
        40,
        45
    };
    
};

#endif