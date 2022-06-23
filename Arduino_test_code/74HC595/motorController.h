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
        Motor(0, 21, 4*STEPCOUNT),
        Motor(1, 21, 4*STEPCOUNT),
        Motor(2, 21, 4*STEPCOUNT),
        Motor(3, 21, 4*STEPCOUNT),
        Motor(4, 21, 4*STEPCOUNT),
        Motor(5, 21, 4*STEPCOUNT),
        Motor(6, 21, 4*STEPCOUNT),
        Motor(7, 21, 4*STEPCOUNT),
        Motor(8, 21, 4*STEPCOUNT),
        Motor(9, 21, 4*STEPCOUNT),
        Motor(10, 21, 4*STEPCOUNT),
    };
    
};

#endif