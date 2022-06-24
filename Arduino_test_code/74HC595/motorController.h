#ifndef _MOTORCONTROLLER_H_
#define _MOTORCONTROLLER_H_


#include <Arduino.h>
#include "motor.h"

class MotorController{
  public:
    MotorController();
    void update();
    void setSteps(int motorID, int stepCount);
    // void getCurrentStep();

    

  private:
    //Pin connected to ST_CP of 74HC595
    static const int latchPin = 17;
    //Pin connected to SH_CP of 74HC595
    static const int clockPin = 16;
    ////Pin connected to DS of 74HC595
    static const int dataPin = 4;

    static const int motorCount = 11;
    Motor motors[motorCount] = {
        Motor(0, 36, 4*STEPCOUNT),
        Motor(1, 39, 4*STEPCOUNT),
        Motor(2, 34, 4*STEPCOUNT),
        Motor(3, 35, 4*STEPCOUNT),
        Motor(4, 32, 4*STEPCOUNT),
        Motor(5, 33, 4*STEPCOUNT),
        Motor(6, 25, 4*STEPCOUNT),
        Motor(7, 26, 4*STEPCOUNT),
        Motor(8, 27, 4*STEPCOUNT),
        Motor(9, 14, 4*STEPCOUNT),
        Motor(10, 12, 4*STEPCOUNT),
    };
    
};

#endif