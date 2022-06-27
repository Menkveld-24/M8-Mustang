int encoder_value = 0;
#define GREEN_A 6
#define WHITE_B 7
#define YELLOW_Z 8
 
void setup() {
  pinMode (GREEN_A, INPUT);
  pinMode (WHITE_B, INPUT);
  pinMode (YELLOW_Z, INPUT);
  Serial.begin (9600);

}
 
void loop() {
  Serial.print(digitalRead(GREEN_A));
  Serial.print(digitalRead(WHITE_B));
  Serial.println(digitalRead(YELLOW_Z));
  // if (DT_pinstate != last_DT_pinstate) { //did DT changed state?
  //   if (digitalRead(CLK_pin) == DT_pinstate) { // if DT changed state, check CLK
  //      encoder_value--; // rotation is clockwise, decrement the value
  //   }else{
  //      encoder_value++; // rotation is counter-clockwise, increment the value
  //   }
  // last_DT_pinstate = DT_pinstate; //save the last state of DT
  // Serial.print("Position: ");
  // Serial.println(encoder_value);
  // }
 
  // last_DT_pinstate = DT_pinstate; // Updates the previous state of DT with the current state
}

// // #include "motor.h"
// #define outputA 6
// #define outputB 7

// int counter = 0; 
// int aState;
// int aLastState;  

// // Motor motor(17,18,19,4);
// // Motor motor1(22, 23, 25, 26);
// // Motor motor2(27, 32, 33, 16);

// void setup(){
//  pinMode (outputA, INPUT);
//  pinMode (outputB, INPUT);
   
//   Serial.begin (115200);
//   // Reads the initial state of the outputA
//   aLastState = digitalRead(outputA); 

//   // motor.setRotation(2000);
//   // motor1.setRotation(1000);
//   // motor2.setRotation(500);
// }

// void loop(){
// //  Serial.println("clockwise");
// //  delay(100);
//   // motor.update();
//   // motor1.update();
//   // motor2.update();
//   readRotary();
// }

// void readRotary(){
//   aState = digitalRead(outputA);
//   if (aState != aLastState){     
//      // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
//     if (digitalRead(outputB) != aState) { 
//        counter ++;
//     } else {
//        counter --;
//     }
//     //  Serial.print("Position: ");
//     Serial.println(counter);
//    } 
//    aLastState = aState; 
// }

// // #define outputA 6
// // #define outputB 7

// //  int counter = 0; 
// //  int aState;
// //  int aLastState;  

// //  void setup() { 
// //    pinMode (outputA,INPUT);
// //    pinMode (outputB,INPUT);
   
// //    Serial.begin (9600);
// //    // Reads the initial state of the outputA
// //    aLastState = digitalRead(outputA);   
// //  } 

// //  void loop() { 
// //    aState = digitalRead(outputA); // Reads the "current" state of the outputA
// //    // If the previous and the current state of the outputA are different, that means a Pulse has occured
// //    if (aState != aLastState){     
// //      // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
// //      if (digitalRead(outputB) != aState) { 
// //        counter ++;
// //      } else {
// //        counter --;
// //      }
// //      Serial.print("Position: ");
// //      Serial.println(counter);
// //    } 
// //    aLastState = aState; // Updates the previous state of the outputA with the current state
// //  }
