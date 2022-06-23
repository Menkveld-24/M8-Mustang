#ifndef _MOTOR_H_
#define _MOTOR_H_

#define STEPCOUNT 2048
#define RPM 10

//superclass
#include <Arduino.h>

class Motor{
  public:
    Motor(byte motorID, byte switchPin, int maxHeight);
    void update(unsigned long currentTime);
    void setRotation(int rot);
    bool getCurrentStep(int pos);
    bool isIdle();
    void returnToHome();
    void extendToTop();

  private:
    byte motorID;
    // pin used to sense the down position at
    byte switchPin;
    // max height the motor can go in steps
    int maxHeight;

    bool rotateClockWise = true;
    // delay to wait between steps
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
    // the current step we are at
    int currentStep = 0;
    // timestamp of last step taken
    unsigned long lastStep = 0;
    // steps left to step
    int stepsLeft = 0;
};

#endif