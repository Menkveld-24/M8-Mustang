#include <Arduino.h>
#include "communicator.h"
#include <esp_now.h>
#include <WiFi.h>

Communicator::Communicator(){
    // // Init ESP-NOW
    // WiFi.mode(WIFI_STA);
    // if (esp_now_init() != 0) Serial.println("Error initializing ESP-NOW");

    // esp_now_register_send_cb(onDataSent);

    // memcpy(this->connectedESPInfo.peer_addr, this->receiverMAC, 6);
    // this->connectedESPInfo.channel = 0;  
    // this->connectedESPInfo.encrypt = false;

    // // Add peer        
    // if (esp_now_add_peer(&this->connectedESPInfo) != ESP_OK){
    //     Serial.println("Failed to add peer");
    // } else {
    //     Serial.println("Added peer: ");
    //     // Serial.println(connectedESPInfo.peer_addr);
    // }

    //Serial initialization
}

void Communicator::initESP(){
    // Init ESP-NOW
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != 0) Serial.println("Error initializing ESP-NOW");

    esp_now_register_send_cb(onDataSent);

    memcpy(this->connectedESPInfo.peer_addr, this->receiverMAC, 6);
    this->connectedESPInfo.channel = 0;  
    this->connectedESPInfo.encrypt = false;

    // Add peer        
    if (esp_now_add_peer(&this->connectedESPInfo) != ESP_OK) Serial.println("Failed to add peer");
    else Serial.println("Added peer: ");

}

// triggered every programm cycle
void Communicator::update(){
    // perhaps a keepalive ping or whatever
}

// triggered on a job change
void Communicator::newJob(byte newJobID){
    Serial.println("Getting a new job");
    this->dataToSend.jobID = newJobID;
    esp_now_send(this->receiverMAC, (uint8_t *) &this->dataToSend, sizeof(this->dataToSend));
    // updateRing(newJobID);
}

// update the unity app over serial comm
void Communicator::updateUnity(byte jobID){

}

// Update the other esp
void Communicator::updateRing(byte jobID){
    this->dataToSend.jobID = jobID;
    esp_now_send(this->receiverMAC, (uint8_t *) &this->dataToSend, sizeof(this->dataToSend));
}

void Communicator::onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status){
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}