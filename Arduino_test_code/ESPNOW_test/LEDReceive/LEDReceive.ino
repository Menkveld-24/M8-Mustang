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
  delay(1000);
  counter++;
  if(counter == 30) counter = 0;
  receivedData.jobID = counter;
  receivedData.isPressed = true;
  
  if(received){
    received = false;
    LEDReceiver(receivedData.jobID);
  } 

  if (receivedData.isPressed){
    receivedData.isPressed = false;
    currentStates.push_back(receivedData.jobID);
    if(currentStates.size() >= 6) currentStates.pop_front();

    Serial.println("Current queue");
    for(int i =0; i< currentStates.size(); i++){
      Serial.println(currentStates[i]);
    }

    saveState(receivedData.jobID);
    // deque<byte> mydeque;


    
  }
}

void normalState(){
  for (int i =0; i<393; i++){
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

void saveState(byte jobID){
  switch (jobID) {
    case 0:
      for (int i = 15; i <= 20; i++) {
        leds[i] = CHSV (stresslevelColor[1][0],stresslevelColor[1][1],stresslevelColor[1][2]);
      }
      for (int i = 230; i <=234; i++){
        leds[i] = CHSV (stresslevelColor[1][0],stresslevelColor[1][1],stresslevelColor[1][2]);
      }
      break;
    case 1:
      for (int i = 8; i <= 13; i++) {
        leds[i] = CHSV (stresslevelColor[0][0], stresslevelColor[0][1], stresslevelColor[0][2]);
      }
      for (int i = 224; i <=228; i++){
        leds[i] = CHSV (stresslevelColor[0][0], stresslevelColor[0][1], stresslevelColor[0][2]);
      }
      break;
    case 2:
      for (int i = 0; i <= 5; i++) {
        leds[i] = CHSV (stresslevelColor[0][0], stresslevelColor[0][1], stresslevelColor[0][2]);
      }
      for (int i = 218; i<=222; i++){
        leds[i] = CHSV (stresslevelColor[0][0], stresslevelColor[0][1], stresslevelColor[0][2]);
      }
      break;
    case 3:
      for (int i = 210; i <= 215; i++) {
        leds [i] = CHSV (stresslevelColor[3][0], stresslevelColor[3][1], stresslevelColor[3][2]);
      }
      for (int i = 387; i<=392; i++){
        leds [i] = CHSV (stresslevelColor[3][0], stresslevelColor[3][1], stresslevelColor[3][2]);
      }
      break;
    case 4:
      for (int i = 203; i <= 208; i++) {
        leds [i] = CHSV (stresslevelColor[3][0], stresslevelColor[3][1], stresslevelColor[3][2]);
      }
      for (int i = 381; i <= 386; i++) {
        leds [i] = CHSV (stresslevelColor[3][0], stresslevelColor[3][1], stresslevelColor[3][2]);
      } 
      break;
    case 5:
      for (int i = 196; i <= 201; i++) {
        leds[i] = CHSV (stresslevelColor[2][0], stresslevelColor[2][1], stresslevelColor[2][2]);
      }
      for (int i = 376; i <= 380; i++) {
        leds[i] = CHSV (stresslevelColor[2][0], stresslevelColor[2][1], stresslevelColor[2][2]);
      }
      break;
    case 6:
      for (int i = 189; i <= 194; i++) {
        leds[i] = CHSV (stresslevelColor[0][0], stresslevelColor[0][1], stresslevelColor[0][2]);
      }
      for (int i = 370; i <= 374; i++) {
        leds[i] = CHSV (stresslevelColor[0][0], stresslevelColor[0][1], stresslevelColor[0][2]);
      }
      break;
    case 7:
      for (int i = 182; i <= 186; i++) {
        leds[i] = CHSV (stresslevelColor[1][0],stresslevelColor[1][1],stresslevelColor[1][2]);
      }
      for (int i = 364; i <= 369; i++) {
        leds[i] = CHSV (stresslevelColor[1][0],stresslevelColor[1][1],stresslevelColor[1][2]);
      }
      break;
    case 8:
      for (int i = 174; i <= 179; i++) {
        leds[i] = CHSV (stresslevelColor[0][0], stresslevelColor[0][1], stresslevelColor[0][2]);
      }
      for (int i = 358; i <= 362; i++) {
        leds[i] = CHSV (stresslevelColor[0][0], stresslevelColor[0][1], stresslevelColor[0][2]);
      }
      break;
    case 9:
      for (int i = 167; i <= 172; i++) {
        leds[i] = CHSV (stresslevelColor[1][0],stresslevelColor[1][1],stresslevelColor[1][2]);
      }
      for (int i = 352; i <= 357; i++) {
        leds[i] = CHSV (stresslevelColor[1][0],stresslevelColor[1][1],stresslevelColor[1][2]);
      }
      break;
    case 10:
      for (int i = 160; i <= 165; i++) {
        leds[i] = CHSV (stresslevelColor[2][0], stresslevelColor[2][1], stresslevelColor[2][2]);
      }
      for (int i = 346; i <= 351; i++) {
        leds[i] = CHSV (stresslevelColor[2][0], stresslevelColor[2][1], stresslevelColor[2][2]);
      }
      break;
    case 11:
      for (int i = 153; i <= 158; i++) {
        leds[i] = CHSV (stresslevelColor[1][0],stresslevelColor[1][1],stresslevelColor[1][2]);
      }
      for (int i = 340; i <= 345; i++) {
        leds[i] = CHSV (stresslevelColor[1][0],stresslevelColor[1][1],stresslevelColor[1][2]);
      }
      break;
    case 12:
      for (int i = 147; i <= 151; i++) {
        leds[i] = CHSV (stresslevelColor[2][0], stresslevelColor[2][1], stresslevelColor[2][2]);
      }
      for (int i = 335; i <= 339; i++) {
        leds[i] = CHSV (stresslevelColor[2][0], stresslevelColor[2][1], stresslevelColor[2][2]);
      }
      break;
    case 13:
      for (int i = 139; i <= 144; i++) {
        leds[i] = CHSV (stresslevelColor[1][0],stresslevelColor[1][1],stresslevelColor[1][2]);
      }
      for (int i = 329; i <= 333; i++) {
        leds[i] = CHSV (stresslevelColor[1][0],stresslevelColor[1][1],stresslevelColor[1][2]);
      }
      break;
    case 14:
      for (int i = 132; i <= 137; i++) {
        leds[i] = CHSV (stresslevelColor[1][0],stresslevelColor[1][1],stresslevelColor[1][2]);
      }
      for (int i = 323; i <= 327; i++) {
        leds[i] = CHSV (stresslevelColor[1][0],stresslevelColor[1][1],stresslevelColor[1][2]);
      }
      break;
    case 15:
      for (int i = 125; i <= 130; i++) {
        leds[i] = CHSV (stresslevelColor[2][0], stresslevelColor[2][1], stresslevelColor[2][2]);
      }
      for (int i = 317; i <= 321; i++) {
        leds[i] = CHSV (stresslevelColor[2][0], stresslevelColor[2][1], stresslevelColor[2][2]);
      }
      break;
    case 16:
      for (int i = 118; i <= 123; i++) {
        leds[i] = CHSV (stresslevelColor[1][0],stresslevelColor[1][1],stresslevelColor[1][2]);
      }
      for (int i = 311; i <= 316; i++) {
        leds[i] = CHSV (stresslevelColor[1][0],stresslevelColor[1][1],stresslevelColor[1][2]);
      }
      break;
    case 17:
      for (int i = 110; i <= 115; i++) {
        leds [i] = CHSV (stresslevelColor[4][0], stresslevelColor[4][1], stresslevelColor[4][2]);
      }
      for (int i = 305; i <= 310; i++) {
        leds [i] = CHSV (stresslevelColor[4][0], stresslevelColor[4][1], stresslevelColor[4][2]);
      }
      break;
    case 18:
      for (int i = 102; i <= 107; i++) {
        leds [i] = CHSV (stresslevelColor[4][0], stresslevelColor[4][1], stresslevelColor[4][2]);
      }
      for (int i = 299; i <= 304; i++) {
        leds [i] = CHSV (stresslevelColor[4][0], stresslevelColor[4][1], stresslevelColor[4][2]);
      }
      break;
    case 19:
      for (int i = 95; i <= 100; i++) {
        leds [i] = CHSV (stresslevelColor[3][0], stresslevelColor[3][1], stresslevelColor[3][2]);
      }
      for (int i = 294; i <= 298; i++) {
       leds [i] = CHSV (stresslevelColor[3][0], stresslevelColor[3][1], stresslevelColor[3][2]);
      }
      break;
    case 20:
      for (int i = 88; i <= 93; i++) {
        leds[i] = CHSV (stresslevelColor[2][0], stresslevelColor[2][1], stresslevelColor[2][2]);
      }
      for (int i = 288; i <= 292; i++) {
        leds[i] = CHSV (stresslevelColor[2][0], stresslevelColor[2][1], stresslevelColor[2][2]);
      }
      break;
    case 21:
      for (int i = 81; i <= 86; i++) {
        leds[i] = CHSV (stresslevelColor[2][0], stresslevelColor[2][1], stresslevelColor[2][2]);
      }
      for (int i = 282; i <= 286; i++) {
        leds[i] = CHSV (stresslevelColor[2][0], stresslevelColor[2][1], stresslevelColor[2][2]);
      }
      break;
    case 22:
      for (int i = 73; i <= 78; i++) {
        leds[i] = CHSV (stresslevelColor[1][0],stresslevelColor[1][1],stresslevelColor[1][2]);
      }
      for (int i = 276; i <= 281; i++) {
        leds[i] = CHSV (stresslevelColor[1][0],stresslevelColor[1][1],stresslevelColor[1][2]);
      }
      break;
    case 23:
      for (int i = 65; i <= 70; i++) {
        leds [i] = CHSV (stresslevelColor[4][0], stresslevelColor[4][1], stresslevelColor[4][2]);
      }
      for (int i = 270; i <= 275; i++) {
        leds [i] = CHSV (stresslevelColor[4][0], stresslevelColor[4][1], stresslevelColor[4][2]);
      }
      break;
    case 24:
      for (int i = 58; i <= 62; i++) {
        leds [i] = CHSV (stresslevelColor[3][0], stresslevelColor[3][1], stresslevelColor[3][2]);
      }
      for (int i = 265; i <= 269; i++) {
        leds [i] = CHSV (stresslevelColor[3][0], stresslevelColor[3][1], stresslevelColor[3][2]);
      }
      break;
    case 25:
      for (int i = 50; i <= 55; i++) {
        leds[i] = CHSV (stresslevelColor[2][0], stresslevelColor[2][1], stresslevelColor[2][2]);
      }
      for (int i = 259; i <= 263; i++) {
        leds[i] = CHSV (stresslevelColor[2][0], stresslevelColor[2][1], stresslevelColor[2][2]);
      }
      break;
    case 26:
      for (int i = 43; i <= 48; i++) {
        leds[i] = CHSV (stresslevelColor[1][0],stresslevelColor[1][1],stresslevelColor[1][2]);
      }
      for (int i = 253; i <= 257; i++) {
        leds[i] = CHSV (stresslevelColor[1][0],stresslevelColor[1][1],stresslevelColor[1][2]);
      }
      break;
    case 27:
      for (int i = 35; i <= 40; i++) {
        leds[i] = CHSV (stresslevelColor[2][0], stresslevelColor[2][1], stresslevelColor[2][2]);
      }
      for (int i = 247; i <= 251; i++) {
        leds[i] = CHSV (stresslevelColor[2][0], stresslevelColor[2][1], stresslevelColor[2][2]);
      }
      break;
    case 28:
      for (int i = 29; i <= 33; i++) {
        leds[i] = CHSV (stresslevelColor[2][0], stresslevelColor[2][1], stresslevelColor[2][2]);
      }
      for (int i = 241; i <= 246; i++) {
        leds[i] = CHSV (stresslevelColor[2][0], stresslevelColor[2][1], stresslevelColor[2][2]);
      }
      break;
    case 29:
      for (int i = 22; i <= 27; i++) {
       leds[i] = CHSV (stresslevelColor[1][0],stresslevelColor[1][1],stresslevelColor[1][2]);
      }
      for (int i = 236; i <= 240; i++) {
        leds[i] = CHSV (stresslevelColor[1][0],stresslevelColor[1][1],stresslevelColor[1][2]);
      }
      break;
    }
    FastLED.show();
}

void LEDReceiver(byte jobID) {
  Serial.println(jobID);
  switch (jobID) {
    case 0:
      for (int i = 15; i <= 20; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 230; i <=234; i++){
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 1:
      for (int i = 8; i <= 13; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 224; i <=228; i++){
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 2:
      for (int i = 0; i <= 5; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 218; i<=222; i++){
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 3:
      for (int i = 210; i <= 215; i++) {
        leds [i] = CHSV (color, saturation, dim);
      }
      for (int i = 387; i<=392; i++){
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 4:
      for (int i = 203; i <= 208; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 381; i <= 386; i++) {
        leds[i] = CHSV (color, saturation, dim);
      } 
      break;
    case 5:
      for (int i = 196; i <= 201; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 376; i <= 380; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 6:
      for (int i = 189; i <= 194; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 370; i <= 374; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 7:
      for (int i = 182; i <= 186; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 364; i <= 369; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 8:
      for (int i = 174; i <= 179; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 358; i <= 362; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 9:
      for (int i = 167; i <= 172; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 352; i <= 357; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 10:
      for (int i = 160; i <= 165; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 346; i <= 351; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 11:
      for (int i = 153; i <= 158; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 340; i <= 345; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 12:
      for (int i = 147; i <= 151; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 335; i <= 339; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 13:
      for (int i = 139; i <= 144; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 329; i <= 333; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 14:
      for (int i = 132; i <= 137; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 323; i <= 327; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 15:
      for (int i = 125; i <= 130; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 317; i <= 321; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 16:
      for (int i = 118; i <= 123; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 311; i <= 316; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 17:
      for (int i = 110; i <= 115; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 305; i <= 310; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 18:
      for (int i = 102; i <= 107; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 299; i <= 304; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 19:
      for (int i = 95; i <= 100; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 294; i <= 298; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 20:
      for (int i = 88; i <= 93; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 288; i <= 292; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 21:
      for (int i = 81; i <= 86; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 282; i <= 286; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 22:
      for (int i = 73; i <= 78; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 276; i <= 281; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 23:
      for (int i = 65; i <= 70; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 270; i <= 275; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 24:
      for (int i = 58; i <= 62; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 265; i <= 269; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 25:
      for (int i = 50; i <= 55; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 259; i <= 263; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 26:
      for (int i = 43; i <= 48; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 253; i <= 257; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 27:
      for (int i = 35; i <= 40; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 247; i <= 251; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 28:
      for (int i = 29; i <= 33; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 241; i <= 246; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    case 29:
      for (int i = 22; i <= 27; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      for (int i = 236; i <= 240; i++) {
        leds[i] = CHSV (color, saturation, dim);
      }
      break;
    }
    FastLED.show();
}

