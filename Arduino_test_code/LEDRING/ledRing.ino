#include <esp_now.h>
#include <WiFi.h>
#include <deque>
#include <FastLED.h>

// Defining the pin 
#define LED_PIN     13
#define BUTTON_PIN  21  

#define RESET -1

// Number of LEDs
#define NUM_LEDS    392

// LEDs variables
CRGBArray<NUM_LEDS> leds;

// colors per stress level chsv colors
int stresslevelColor[5][3]={
    {HUE_GREEN, 255, 75},
    {72, 255, 75},
    {48, 255, 75},
    {24, 255, 75},
    {0, 255, 75}
};

//the time between each transition
int transitionTime[5]= {
    10, 11, 12, 14, 16
};

//start endstart, end, endend
// 15-20, 230-234
const int ledJobs[30][4] = {
    { 15, 20, 230, 234 },
    { 8, 13, 224, 228 },
    { 0, 5, 218, 222 },
    { 210, 215, 387, 392 },
    { 201, 208, 381, 386 },
    { 194, 200, 376, 380 },
    { 188, 193, 370, 374 },
    { 181, 186, 364, 369 },
    { 173, 179, 358, 362 },
    { 166, 172, 352, 357 },
    { 158, 165, 346, 351 },
    { 153, 157, 340, 345 },
    { 144, 150, 335, 339 },
    { 137, 143, 329, 333 },
    { 132, 135, 323, 327 },
    { 124, 128, 317, 321 },
    { 116, 121, 311, 316 },
    { 108, 114, 305, 310 },
    { 102, 107, 299, 304 },
    { 94, 100, 294, 298 },
    { 87, 91, 288, 292 },
    { 81, 86, 282, 286 },
    { 73, 78, 276, 281 },
    { 65, 71, 270, 275 },
    { 58, 63, 265, 269 },
    { 50, 55, 259, 263 },
    { 43, 48, 253, 257 },
    { 35, 41, 247, 251 },
    { 29, 34, 241, 246 },
    { 22, 27, 236, 240 }
};

//number of distress state 1-5, used as index in the stresslevelcolor -1
const int jobStressStates[30] = {
    1,
    0,
    0,
    3,
    3,
    2,
    0,
    1,
    0,
    1,
    2,
    0,
    2,
    1,
    1,
    0,
    1,
    4,
    4,
    3,
    2,
    2,
    1,
    4,
    3,
    2,
    1,
    2,
    0,
    1
};

// Message from sender 
typedef struct message_format {
    byte jobID;
    bool buttonIsPressed;
} message_format;
// Defining the message from sender with receivedData variable 
message_format receivedData;

// Saving state for dequing 
std::deque<byte> currentJobsInState;

bool dataReceived = false;
byte previousJobID;


void setup(){
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
  
    // Init ESP-NOW
    if (esp_now_init() != 0) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    //registering espnow callback
    esp_now_register_recv_cb(onDataReceive);

    pinMode(LED_PIN, OUTPUT);
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);

    turnOffAllLeds();
    FastLED.show();
}

void loop(){
    if(dataReceived) processOnDataReceive();
}

//called once after we received data
void processOnDataReceive(){
    Serial.println("Processing data...");
    dataReceived = false;

    if(receivedData.jobID == RESET){
        turnOffAllLeds();
        Serial.println("Reset the led ring!");
        return;
    }
    //button is pressed, move deque
    if(receivedData.buttonIsPressed){
        turnOnLedToState(receivedData.jobID);

        //add to deque
        currentJobsInState.push_back(receivedData.jobID);
        //deque is full, empty first item and set leds to white
        if(currentJobsInState.size() >= 6) {
            Serial.println("Deque too long...");
            turnOffLed(currentJobsInState[0]);
            currentJobsInState.pop_front();
        }

    } else {
        //deselecting the current led 
        bool isCurrentlySelected = false;
        for(int i = 0; i < currentJobsInState.size(); i++){
            //if in deque set to state color
            if(currentJobsInState[i] == previousJobID) {
                turnOnLedToState(previousJobID);
                isCurrentlySelected = true;
                break;
            }
        }
        //not in deque and not seleted anymore
        if(!isCurrentlySelected) {
            turnOffLed(previousJobID);
        }
        turnOnLedWhite(receivedData.jobID);
    }
    previousJobID = receivedData.jobID;
    FastLED.show();
}

//set the selected job leds to the correct stress state
void turnOnLedToState(byte jobID){
    Serial.print("Turning leds to state for job: ");
    Serial.print(jobID);
    Serial.print(" and state: ");
    Serial.println(jobStressStates[jobID]);

    for(int i = ledJobs[jobID][0]; i < ledJobs[jobID][1]+1; i++ ){
        leds[i] = CHSV(
            stresslevelColor[jobStressStates[jobID]][0],
            stresslevelColor[jobStressStates[jobID]][1],
            stresslevelColor[jobStressStates[jobID]][2]
        );
    }

    for(int i = ledJobs[jobID][2]; i < ledJobs[jobID][3]+1; i++ ){
        leds[i] = CHSV(
            stresslevelColor[jobStressStates[jobID]][0],
            stresslevelColor[jobStressStates[jobID]][1],
            stresslevelColor[jobStressStates[jobID]][2]
        );
    }
}

//turn on the job to black
void turnOffLed(byte jobID){
    Serial.print("Turning leds to black for job: ");
    Serial.println(jobID);

    for(int i = ledJobs[jobID][0]; i < ledJobs[jobID][1]+1; i++ ){
        leds[i] = CRGB::Black;
    }

    for(int i = ledJobs[jobID][2]; i < ledJobs[jobID][3]+1; i++ ){
        leds[i] = CRGB::Black;
    }
}

//turn on the job to white
void turnOnLedWhite(byte jobID){
    Serial.print("Turning leds to white for job: ");
    Serial.println(jobID);

    for(int i = ledJobs[jobID][0]; i < ledJobs[jobID][1]+1; i++ ){
        leds[i] = CHSV(100, 0, 50);
    }

    for(int i = ledJobs[jobID][2]; i < ledJobs[jobID][3]+1; i++ ){
        leds[i] = CHSV(100, 0, 50);
    }
}

// on data receive from master esp 
void onDataReceive(const uint8_t * mac, const uint8_t *incomingData, int len){
    Serial.println("Received data!");
    memcpy(&receivedData, incomingData, sizeof(receivedData));
    Serial.print("JOB ID: ");
    Serial.println(receivedData.jobID);
    Serial.print("Button pressed: ");
    Serial.println(receivedData.buttonIsPressed);

    dataReceived = true;
}

//turning off all the leds
void turnOffAllLeds(){
    for(int i = 0; i < NUM_LEDS; i++){
        leds[i] = CRGB::Black;
    }
}