#ifndef _MOTOR_H_
#define _MOTOR_H_

#define STEPCOUNT 2048
#define RPM 10

//superclass
#include <Arduino.h>

class Motor{
  public:
    Motor(int motorID);
    void update(unsigned long currentTime);
    void setRotation(int rot);
    bool getCurrentStep(int pos);

  private:
    int motorID;
    static const unsigned long stepDelay = 60L * 1000L * 1000L / STEPCOUNT / RPM;

// * Step C0 C1 C2 C3
// *    1  1  1  0  0  
// *    2  0  1  1  0  
// *    3  0  0  1  1 
// *    4  1  0  0  1 
    const bool steps[4][4] = {
        {true, true, false, false},
        {false, true, true, false},
        {false, false, true, true},
        {true, false, false, true}
    };
    int currentStep = 0;
    unsigned long lastStep = 0;
    int stepsLeft = 0;
};

#endif