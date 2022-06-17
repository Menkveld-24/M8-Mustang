// * The sequence of control signals for 4 control wires is as follows:
// *
// * Step C0 C1 C2 C3
// *    1  1  1  0  0  11001100
// *    2  0  1  1  0  01100110
// *    3  0  0  1  1  00110011
// *    4  1  0  0  1  10011001
//byte STEPS [] = {
//149,  //  5,
//166,      //  6,
//106,      //  10,
//89      //  9
//};

byte STEPS [] = {
  51,
  102,
  204,
  153
};

// byte STEPS [] = {
//   170,
//   102,
//   85,
//   153  
// };

//byte STEPS [] = {
//  169,
//  101,
//  86,
//  154
//};

//Pin connected to ST_CP of 74HC595
int latchPin = 17;
//Pin connected to SH_CP of 74HC595
int clockPin = 16;
////Pin connected to DS of 74HC595
int dataPin = 4;

// //byte currentStep = 0; // 0-3 steps, index of STEPS
// bool toggle = false;
// #define outputA 6
//  #define outputB 7

 int counter = 0; 
 int aState;
 int aLastState;  
unsigned long step_delay = 0;

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  

  step_delay = 60L * 1000L * 1000L / 2048 / 10;
  Serial.begin (9600);
  Serial.println("Started shift register");
}

void loop() {
  Serial.println("At start of loop");
  stepm(300);
}
int step_number = 0;

void stepm(int steps){
  unsigned long last_step_time = 0;
  int steps_left = steps;

  while (steps_left > 0)
  {
    unsigned long now = micros();
    // move only if the appropriate delay has passed:
    if (now - last_step_time >= step_delay) {
      // get the timeStamp of when you stepped:
      last_step_time = now;
      // increment or decrement the step number,
      // depending on direction:
        step_number++;
        if (step_number == 1024) {
          step_number = 0;
        }
      // decrement the steps left:
      steps_left--;
      // step the motor to step number 0, 1, ..., {3 or 10}
        stepotor(step_number % 4);
  }
}
}
/*
 * Moves the motor forward or backwards.
 */
void stepotor(int thisStep)
{
//  if (this->pin_count == 4) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, STEPS[thisStep]);
    digitalWrite(latchPin, HIGH);
}






































// //**************************************************************//
// //  Name    : shiftOutCode, Hello World
// //  Author  : Carlyn Maw,Tom Igoe, David A. Mellis
// //  Date    : 25 Oct, 2006
// //  Modified: 23 Mar 2010
// //  Version : 2.0
// //  Notes   : Code for using a 74HC595 Shift Register           //
// //          : to count from 0 to 255
// //****************************************************************

// // * The sequence of control signals for 4 control wires is as follows:
// // *
// // * Step C0 C1 C2 C3
// // *    1  1  0  1  0  10101001
// // *    2  0  1  1  0  01100101
// // *    3  0  1  0  1  01010110
// // *    4  1  0  0  1  10011010
// //byte STEPS [] = {
// //149,  //  5,
// //166,      //  6,
// //106,      //  10,
// //89      //  9
// //};

// byte STEPS [] = {
//   170,
//   102,
//   85,
//   153  
// };

// //byte STEPS [] = {
// //  169,
// //  101,
// //  86,
// //  154
// //};

// //Pin connected to ST_CP of 74HC595
// int latchPin = 17;
// //Pin connected to SH_CP of 74HC595
// int clockPin = 16;
// ////Pin connected to DS of 74HC595
// int dataPin = 4;

// //byte currentStep = 0; // 0-3 steps, index of STEPS
// bool toggle = false;
// #define outputA 6
//  #define outputB 7

//  int counter = 0; 
//  int aState;
//  int aLastState;  
// unsigned long step_delay = 0;

// void setup() {
//   //set pins to output so you can control the shift register
//   pinMode(latchPin, OUTPUT);
//   pinMode(clockPin, OUTPUT);
//   pinMode(dataPin, OUTPUT);
//   pinMode(13, OUTPUT);
//   step_delay = 60L * 1000L * 1000L / 1024 / 10;
//   pinMode (outputA,INPUT);
//    pinMode (outputB,INPUT);
   
//    Serial.begin (9600);
//    // Reads the initial state of the outputA
//    aLastState = digitalRead(outputA);  
// }

// void loop() {
//   aState = digitalRead(outputA); // Reads the "current" state of the outputA
//      // If the previous and the current state of the outputA are different, that means a Pulse has occured
//      if (aState != aLastState){     
//        // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
//        if (digitalRead(outputB) != aState) { 
//          counter ++;
//        } else {
//          counter --;
//        }
//        Serial.print("Position: ");
//        Serial.println(counter);
//      } 
//      aLastState = aState; // Updates the previous state of the outputA with the current state
// //  stepm(300);
// }
// int step_number = 0;

// void stepm(int steps){
//   unsigned long last_step_time = 0;
//   int steps_left = steps;
//   while (steps_left > 0)
//   {
//     unsigned long now = micros();
//     // move only if the appropriate delay has passed:
//     if (now - last_step_time >= step_delay) {
//       // get the timeStamp of when you stepped:
//       last_step_time = now;
//       // increment or decrement the step number,
//       // depending on direction:
//         step_number++;
//         if (step_number == 1024) {
//           step_number = 0;
//         }
//       // decrement the steps left:
//       steps_left--;
//       // step the motor to step number 0, 1, ..., {3 or 10}
//         stepotor(step_number % 4);
//   }
// }
// }
// /*
//  * Moves the motor forward or backwards.
//  */
// void stepotor(int thisStep)
// {
// //  if (this->pin_count == 4) {
//     digitalWrite(latchPin, LOW);
//     shiftOut(dataPin, clockPin, MSBFIRST, STEPS[thisStep]);
//     digitalWrite(latchPin, HIGH);
// }
