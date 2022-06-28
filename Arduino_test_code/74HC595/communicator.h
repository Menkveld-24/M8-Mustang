#ifndef _COMMUNICATOR_H_
#define _COMMUNICATOR_H_

#include <Arduino.h>
#include <esp_now.h>

class Communicator{
    public:
        Communicator();
        void update();
        void initESP();
        void newJob(byte newJobID);
        static void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
        static void onDataReceive(const uint8_t * mac, const uint8_t *incomingData, int len);

    private:
        void updateUnity(byte jobID);
        void updateRing(byte jobID); 

        const uint8_t receiverMAC[6] = {0x30, 0xC6, 0xF7, 0x04, 0x1F, 0x74};
        // const uint8_t receiverMAC[6] = {0x0C, 0xB8, 0x15, 0xC3, 0x10, 0xAC};

        typedef struct message_format {
            int jobID = 0;
            bool booleanTest = false;
        } message_format;

        message_format receivedData;
        message_format dataToSend;
        esp_now_peer_info_t connectedESPInfo;

};

#endif