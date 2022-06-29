#include <espnow.h>
#include <WiFi.h>

byte loopNr = 0;
// Message from sender 
typedef struct message_format {
  byte jobID;
  bool isPressed = false;
} message_format;

const uint8_t receiverMAC[6] = {0x30, 0xC6, 0xF7, 0x04, 0x1F, 0x74};

// Defining the message from sender with receivedData variable 
message_format dataToSend;

// Connecting to other ESP
// esp_now_peer_info_t connectedESPInfo;

void setup() {
    WiFi.mode(WIFI_STA);
    Serial.begin(115200);
    if (esp_now_init() != 0) Serial.println("Error initializing ESP-NOW");

    esp_now_register_send_cb(onDataSent);

    // memcpy(connectedESPInfo.peer_addr, receiverMAC, 6);
    // connectedESPInfo.channel = 0;  
    // connectedESPInfo.encrypt = false;

    // Add peer        
    if (esp_now_add_peer(&connectedESPInfo) != ESP_OK) Serial.println("Failed to add peer");
    else Serial.println("Added peer: ");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);

  dataToSend.jobID = loopNr;
  Serial.print(dataToSend.jobID);
  Serial.println(" Sent to esp...");
  
  esp_now_send(receiverMAC, (uint8_t *) &dataToSend, sizeof(dataToSend));
  loopNr = 4 ;
}


void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status){
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}