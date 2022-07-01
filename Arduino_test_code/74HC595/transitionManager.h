#ifndef _TRANSITIONMANAGER_H_
#define _TRANSITIONMANAGER_H_

#include <Arduino.h>
#define STILL_TRANSITIONING 100
#define FADE_OUT_DELAY 6
#define BUTTON_LED 15

class TransitionManager{
    public:
        TransitionManager();
        void update();
        byte selectButtonPressed(byte currentJob);
        static byte getMotorDuration(byte stressLevel);
        static byte getAnimationDuration(byte stressLevel);
        bool canReturnToIdle();

        //all the stress levels corresponding to a job
        const byte jobStressLevel[30] = {
            2,
            1,
            2,
            4,
            4,
            3,
            1,
            2,
            1,
            2,
            3,
            1,
            3,
            2,
            2,
            1,
            2,
            5,
            5,
            4,
            3,
            3,
            2,
            5,
            4,
            3,
            2,
            3,
            1,
            2
        };
        // the durations of going from idle to a stress level (s)
        inline constexpr static byte motorDelays[5] = { 4, 4, 6, 8, 10 };
        inline constexpr static byte transitionDelays[5] = { 9, 9, 10, 12, 14 };
    
    private:
        bool alreadyTransitioning = false;
        bool alreadyToIdle = true;
        unsigned long timeSinceLastButtonPress;
        byte currentStressLevel;
};

#endif