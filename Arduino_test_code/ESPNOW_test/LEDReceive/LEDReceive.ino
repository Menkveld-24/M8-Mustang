// Including Libraries
#include <esp_now.h>
#include <WiFi.h>
#include <FastLED.h>
#include <deque>

// Defining the pin 
#define LED_PIN     13
#define BUTTON_PIN  21

// Number of LEDs
#define NUM_LEDS    392

using namespace std;

// LEDs variables
CRGBArray<NUM_LEDS> leds;
byte color = 0; // white
byte dim = 255; // no dim for the chosen one
byte saturation = 0;
bool received = false;
byte stresslevelColor[5][3]={
  {85, 71, 97},
  {66, 69, 95},
  {48, 67, 89},
  {29, 79, 76},
  {7, 76, 55}
};

// MAC Address
uint8_t senderMAC[] = {0x0C, 0xB8, 0x15, 0xC3, 0x10, 0xAC};
// uint8_t senderMAC[] = {0x30, 0xC6, 0xF7, 0x04, 0x1F, 0x74};

// Message from sender 
typedef struct message_format {
  byte jobID;
  bool isPressed = false;
} message_format;

// Defining the message from sender with receivedData variable 
message_format receivedData;

// Connecting to other ESP
esp_now_peer_info_t connectedESPInfo;

// Saving state for dequing 
deque<byte> currentStates;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  
  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    // return;
  }

   // naming the receiving variable
  esp_now_register_recv_cb(onDataReceive);

 // Add peer
  memcpy(connectedESPInfo.peer_addr, senderMAC, 6);
  connectedESPInfo.channel = 0;
  connectedESPInfo.encrypt = false;
  if (esp_now_add_peer(&connectedESPInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
  } else {
    Serial.println("Added peer knl: ");
  }

  // Serial.println("Started program!");
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);

  // Defining the deque 

}

byte counter = 0;

void loop() {
  normalState();
  // LEDReceiver(24);
  // Serial.println("l");
  receivedData.isPressed = true;
  
  if(received){
    received = false;
    turnOnLEDS(receivedData.jobID);
  } 

  if (receivedData.isPressed){
    receivedData.isPressed = false;
    currentStates.push_back(receivedData.jobID);
    if(currentStates.size() >= 6) currentStates.pop_front();

    Serial.println("Current queue");
    for(int i =0; i< currentStates.size(); i++){
      Serial.println(currentStates[i]);
    }

    turnOnLEDS(receivedData.jobID);
    // deque<byte> mydeque;
  }
}

void normalState(){
  for (int i =0; i<NUM_LEDS; i++){
    leds[i] = CRGB::Black;
  }
}

void onDataReceive(const uint8_t * mac, const uint8_t *incomingData, int len) {
  Serial.println("Received data!");
  memcpy(&receivedData, incomingData, sizeof(receivedData));
  Serial.print("JOB ID: ");
  Serial.println(receivedData.jobID);
  // Serial.print("TestBool: ");
  // Serial.println(receivedData.isPressed);
  received = true;
  // LEDReceiver(receivedData.jobID);
  // stressStateLED(receivedData.lastState);
}

void turnOnLEDSstate(int startLED, int endLED, byte distressState){
  for (int i = startLED; i <= endLED; i++) {
    leds[i] = CHSV (stresslevelColor[distressState][0],stresslevelColor[distressState][1],stresslevelColor[distressState][2]);
  }
}

void turnOnLEDS(byte jobID){
  switch (jobID) {
    case 0:
    //Nurse
      turnOnLEDSstate(15, 20, 1);
      turnOnLEDSstate(230, 234, 1);
      break;
    case 1:
    // Software Developer
      turnOnLEDSstate(8, 13, 0);
      turnOnLEDSstate(224,228,0);
      break;
    case 2:
    //Dental Technician
      turnOnLEDSstate(0, 5, 0);
      turnOnLEDSstate(218, 222, 0);
      break;
    case 3:
    //Taxi Driver
      turnOnLEDSstate(210, 215, 3);
      turnOnLEDSstate(387,392,3);
      break;
    case 4:
    //Newspaper reporter
      turnOnLEDSstate(203, 208, 3);
      turnOnLEDSstate(381, 386, 3);
      break;
    case 5:
    //Chef
      turnOnLEDSstate(196, 201, 2);
      turnOnLEDSstate(376, 380, 2);
      break;
    case 6:
    //University professor
      turnOnLEDSstate(189, 194, 0);
      turnOnLEDSstate(370, 374, 0);
      break;
    case 7:
    //Aerospace engineer
      turnOnLEDSstate(182, 186, 1);
      turnOnLEDSstate(364, 369, 1);
      break;
    case 8:
    //Hair styilist
      turnOnLEDSstate(174, 179, 0);
      turnOnLEDSstate(358, 362, 0);
      break;
    case 9:
    //Electrical engineer
      turnOnLEDSstate(167, 172, 1);
      turnOnLEDSstate(352, 357, 1);
      break;
    case 10:
    //Surgeon
      turnOnLEDSstate(160, 165, 2);
      turnOnLEDSstate(346, 351, 2);
      break;
    case 11:
    //Pharmacist
      turnOnLEDSstate(153,158, 1);
      turnOnLEDSstate(340, 345, 1);
      break;
    case 12:
    //Social Media Manager
      turnOnLEDSstate(147, 151, 2);
      turnOnLEDSstate(335, 339, 2);
      break;
    case 13:
    //Accountant
      turnOnLEDSstate(139, 144, 1);
      turnOnLEDSstate(329, 333, 1);
      break;
    case 14:
    //Dentist
      turnOnLEDSstate(132, 137, 1);
      turnOnLEDSstate(323, 327, 1);
      break;
    case 15:
    //Tailor
      turnOnLEDSstate(125, 130, 2);
      turnOnLEDSstate(317, 321, 2);
      break;
    case 16:
    //Plumber
      turnOnLEDSstate(118, 123, 1);
      turnOnLEDSstate(311, 316, 1);
      break;
    case 17:
    //Military General
      turnOnLEDSstate(110, 115, 4);
      turnOnLEDSstate(305, 310, 4);
      break;
    case 18:
    //Pilot
      turnOnLEDSstate(102, 107, 4);
      turnOnLEDSstate(299, 304, 4);
      break;
    case 19:
    //Corporate exectuive
      turnOnLEDSstate(95, 100, 3);
      turnOnLEDSstate(294, 298, 3);
      break;
    case 20:
    //Construction Laborer
      turnOnLEDSstate(88, 93, 2);
      turnOnLEDSstate(288, 292, 2);
      break;
    case 21:
    //Attorney
      turnOnLEDSstate(81, 86, 2);
      turnOnLEDSstate(282, 286, 2);
      break;
    case 22:
    //Physicist
      turnOnLEDSstate(73, 78, 1);
      turnOnLEDSstate(276, 281, 1);
      break;
    case 23:
    //Firefighter
      turnOnLEDSstate(65, 70, 4);
      turnOnLEDSstate(270,275, 4);
      break;
    case 24:
    //Police officer
      turnOnLEDSstate(58, 62, 3);
      turnOnLEDSstate(265, 269, 3);
      break;
    case 25:
    //Fashion Designer
      turnOnLEDSstate(50, 55, 2);
      turnOnLEDSstate(259,263, 2);
      break;
    case 26:
    //Industrial Designer
      turnOnLEDSstate(43, 48, 1);
      turnOnLEDSstate(253, 257, 1);
      break;
    case 27:
    //Nuclear engineer
      turnOnLEDSstate(35, 40, 2);
      turnOnLEDSstate(247, 251, 2);
      break;
    case 28:
    //Computer programmer
      turnOnLEDSstate(29, 33, 2);
      turnOnLEDSstate(241, 246, 2);
      break;
    case 29:
    //Veterenarian
      turnOnLEDSstate(22, 27, 1);
      turnOnLEDSstate(236, 240 ,1);
      break;
    }
    FastLED.show();
}