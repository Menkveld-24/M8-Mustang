#include <Arduino.h>
#include "communicator.h"
#include <esp_now.h>
#include <WiFi.h>

Communicator::Communicator(){}

// this fails if it is in the main constructor smh
void Communicator::initESP(){
    // Init ESP-NOW
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != 0) // Serial.println("Error initializing ESP-NOW");

    esp_now_register_send_cb(onDataSent);

    memcpy(this->connectedESPInfo.peer_addr, this->receiverMAC, 6);
    this->connectedESPInfo.channel = 0;  
    this->connectedESPInfo.encrypt = false;

    // Add peer        
    if (esp_now_add_peer(&this->connectedESPInfo) != ESP_OK) return;
    // else Serial.println("Added peer: ");

}

// triggered every programm cycle
void Communicator::update(){
    // perhaps a keepalive ping or whatever
}

// triggered on a job change
void Communicator::newJob(byte newJobID){
    updateRing(newJobID, false);
}

// triggered on a job change
void Communicator::newJobSelected(byte newJobID, byte nextLevel){
    // Serial.println("Getting a new job pressed!");
    updateUnity(newJobID);
    updateRing(newJobID, true);
}

// update the unity app over serial comm
void Communicator::updateUnity(byte jobID){
    Serial.flush();
    Serial.print(static_cast<int>(jobID));
}

// Update the other esp with job id and button state
void Communicator::updateRing(byte jobID, bool buttonPressed){
    this->dataToSend.jobID = jobID;
    this->dataToSend.buttonPressed = buttonPressed;
    // Serial.println(this->dataToSend.buttonPressed);
    esp_now_send(this->receiverMAC, (uint8_t *) &this->dataToSend, sizeof(this->dataToSend));
}

// espnow send callback
void Communicator::onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status){
    // Serial.print("\r\nLast Packet Send Status:\t");
    // Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}