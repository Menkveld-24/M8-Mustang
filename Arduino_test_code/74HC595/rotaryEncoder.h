#ifndef _ROTARYENCODER_H_
#define _ROTARYENCODER_H_

#include <Arduino.h>

class RotaryEncoder{
    public:
        RotaryEncoder();
        int listenForJobChange();

    private:
        int getCurrentJobID();
        int position = 0;
        byte previousJob = 0;
        bool previousState = false;
};


#endif