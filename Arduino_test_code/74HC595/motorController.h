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
        Motor(0),
        Motor(1),
        Motor(2),
        Motor(3),
        Motor(4),
        Motor(5),
        Motor(6),
        Motor(7),
        Motor(8),
        Motor(9),
        Motor(10),
    };
    
};

#endif