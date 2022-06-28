#ifndef _ROTARYENCODER_H_
#define _ROTARYENCODER_H_

#include <Arduino.h>
#include <vector>
#include <deque>
#include <unordered_map>

#define STEPS_PER_ROTATION 40
#define JOBCOUNT 30
#define PINA 22
#define PINB 23
#define SAMPLING_DELAY 1/10000

class RotaryEncoder{
    public:
        RotaryEncoder();
        void update();
        int listenForJobChange();

    private:
        int getCurrentJobID();
        int position = 0;
        std::deque <int> previousPositions;
        byte previousJob = 0;
        unsigned long lastMeasure = 0;
        bool previousStateA = false;
        bool previousStateB = false;
};


#endif