#ifndef _COMMUNICATOR_H_
#define _COMMUNICATOR_H_

#include <Arduino.h>

class Communicator{
    public:
        Communicator();
        void update();
        void newJob();
    private:
        void updateUnity(byte jobID);
        void updateRing(byte jobID); 
};

#endif