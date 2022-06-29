// #include <esp_now.h>
// #include <WiFi.h>

// uint8_t receiverMAC[] = {0x0C, 0xB8, 0x15, 0xC3, 0x10, 0xAC};
// // // uint8_t receiverMAC[] = {0x30, 0xC6, 0xF7, 0x04, 0x1F, 0x74};

// typedef struct message_format {
//     byte testValue = 0;
//     bool booleanTest = false;
// } message_format;

// message_format receivedData;
// message_format dataToSend;

// esp_now_peer_info_t connectedESPInfo;

// void setup(){
//     Serial.begin(115200);
    
//     WiFi.mode(WIFI_STA);
//     // Init ESP-NOW
//     if (esp_now_init() != 0) {
//         Serial.println("Error initializing ESP-NOW");
//         // return;
//     }
    
//     esp_now_register_send_cb(onDataSent);
//     esp_now_register_recv_cb(onDataReceive);
    
//     memcpy(connectedESPInfo.peer_addr, receiverMAC, 6);
//     connectedESPInfo.channel = 0;  
//     connectedESPInfo.encrypt = false;

//     // Add peer        
//     if (esp_now_add_peer(&connectedESPInfo) != ESP_OK){
//         Serial.println("Failed to add peer");
//     } else {
//         Serial.println("Added peer: ");
//         // Serial.println(connectedESPInfo.peer_addr);
//     }

//     Serial.println("Started program!");
// }

// // void loop(){
// //     delay(1000);
// //     Serial.println("hoi");
// // }

// void loop(){
//     esp_now_send(receiverMAC, (uint8_t *) &dataToSend, sizeof(dataToSend));
//     Serial.println("Sent data to other esp...");
//     delay(5000);
//     dataToSend.testValue++;
// }

// void onDataReceive(const uint8_t * mac, const uint8_t *incomingData, int len){
//     Serial.println("Received data!");
//     memcpy(&receivedData, incomingData, sizeof(receivedData));
//     Serial.print("TestValue: ");
//     Serial.println(receivedData.testValue);
//     Serial.print("TestBool: ");
//     Serial.println(receivedData.booleanTest);
// }

// void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status){
//     Serial.print("\r\nLast Packet Send Status:\t");
//     Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
// }