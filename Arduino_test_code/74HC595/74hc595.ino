#include "motorController.h"

MotorController controller;

void setup(){
    Serial.begin(9600);
    Serial.print("Started program!");
}


void loop(){
    controller.update();
}