
#include <Encoder.h>
#include "LedControl.h"
#include "binary.h"
#include <stdio.h>
#include <stdint.h>
/*
 DIN connects to pin 12
 CLK connects to pin 11
 CS connects to pin 10 
*/
LedControl callStationFloorIndicator = LedControl(12,11,10,1);

LedControl elevatorFloorIndicator = LedControl(9,8,7,1);
Encoder knob(2, 3);



byte lcdDef[][8] = {
 { B00000000, B00011100, B00100010, B00100110, B00101010, B00110010, B00100010, B00011100}, //0
 { B00000000, B00001000, B00011000, B00001000, B00001000, B00001000, B00001000, B00011100}, //1
 { B00000000, B00011100, B00100010, B00000010 ,B00001100, B00010000, B00100000, B00111110}, //2
 { B00000000, B00011100, B00100010, B00000010 ,B00001100, B00000010, B00100010, B00011100}, //3
 { B00000000, B00000100, B00001100, B00010100 ,B00100100, B00111110, B00000100, B00000100}, //4
 { B00000000, B00111110, B00100000, B00100000 ,B00111100, B00000010, B00100010, B00011100}, //5
 { B00000000, B00011100, B00100010, B00100000, B00111100, B00100010, B00100010, B00011100}, //6
 { B00000000, B00111110, B00000010, B00000100, B00001000, B00010000, B00010000, B00010000}, //7
 { B00000000, B00011100, B00100010, B00100010, B00011100, B00100010, B00100010, B00011100}, //8
 { B00000000, B00011100, B00100010, B00100010, B00011110, B00000010, B00100010, B00011100}, //9
 { B00000000, B00001000, B00010100, B00100010, B00100010, B00111110, B00100010, B00100010}, //A
 { B00000000, B00111100, B00100010, B00100010, B00111100, B00100010, B00100010, B00111100}, //B
 { B00000000, B00011100, B00100010, B00100000, B00100000, B00100000, B00100010, B00011100}, //C
 { B00000000, B00111100, B00100010, B00100010, B00100010, B00100010, B00100010, B00111100}, //D
 { B00000000, B00111110, B00100000, B00100000, B00111100, B00100000, B00100000, B00111110}, //E
 { B00000000, B00111110, B00100000, B00100000, B00111100, B00100000, B00100000, B00100000}, //F
 { B00000000, B00011100 ,B00100010, B00100000, B00100000, B00100110, B00100010, B00011100}, //G
 { B00000000, B00100010, B00100010, B00100010, B00111110, B00100010, B00100010, B00100010}, //H
 { B00000000, B00011100, B00001000, B00001000, B00001000, B00001000, B00001000, B00011100}, //I
 { B00000000, B00000010, B00000010, B00000010, B00000010, B00100010, B00100010, B00011100}, //J
 { B00000000, B00100010, B00100100, B00101000, B00110000, B00101000, B00100100, B00100010}, //K
 { B00000000, B00100000, B00100000, B00100000, B00100000, B00100000, B00100000, B00111110}, //L
 { B00000000, B00100010, B00110110, B00101010, B00101010, B00100010, B00100010, B00100010}, //M
 { B00000000, B00100010, B00100010, B00110010, B00101010, B00100110, B00100010, B00100010}, //N
 { B00000000, B00011100, B00100010, B00100010, B00100010, B00100010, B00100010, B00011100}, //O
 { B00000000, B00111100, B00100010, B00100010, B00111100, B00100000, B00100000, B00100000}, //P
 { B00000000, B00011100, B00100010, B00100010, B00100010, B00101010, B00100100, B00011010}, //Q
 { B00000000, B00111100, B00100010, B00100010, B00111100, B00101000, B00100100, B00100010}, //R
 { B00000000, B00011100, B00100010, B00100000, B00011100, B00000010, B00100010, B00011100}, //S
 { B00000000, B00111110, B00001000, B00001000, B00001000, B00001000, B00001000, B00001000}, //T
 { B00000000, B00100010, B00100010, B00100010, B00100010, B00100010, B00100010, B00011100}, //U
 { B00000000, B00100010, B00100010, B00100010, B00100010, B00100010, B00010100, B00001000}, //V
 { B00000000, B00100010, B00100010, B00100010, B00101010, B00101010, B00110110, B00100010}, //W
 { B00000000, B00100010, B00100010, B00010100, B00001000, B00010100, B00100010, B00100010}, //X
 { B00000000, B00100010, B00100010, B00100010, B00010100, B00001000, B00001000, B00001000}, //Y
 { B00000000, B00111110, B00000010, B00000100, B00001000, B00010000, B00100000, B00111110}, //Z
 { B00000000, B00011100, B00100010, B00000100, B00001000, B00001000, B00000000, B00001000}, //?
 { B00000000, B00001000, B00001000, B00001000, B00001000, B00001000, B00000000, B00001000}, //!
 { B00000000, B00110010, B00110010, B00000100, B00001000, B00010000, B00100110, B00100110}, //%
 { B00000000, B00000000, B00010100, B00000000, B00100010, B00011100, B00000000, B00000000}, //:)
 { B00000000, B00000000, B00010100, B00000000, B00011100, B00100010, B00000000, B00000000}, //:(
 { B00000000, B00001000, B00011100, B00101010, B00001000, B00001000, B00001000, B00001000}, // UP ARROW
 { B00001000, B00001000, B00001000, B00001000, B00101010, B00011100, B00001000, B00000000}, // DOWN ARROW  
 { B00000000, B00000000, B00010000, B00100000, B01111111, B00100000, B00010000, B00000000}, // LEFT ARROW
 { B00000000, B00000000, B00001000, B00000100, B11111110, B00000100, B00001000, B00000000}  // RIGHT ARROW
};




long numFloors = sizeof(lcdDef) / 8;
#define DOVER_BUZZ_PIN 32
#define ENCODER_PUSH_SWITCH_PIN 5
#define DINNER_BELL_PIN A8

#define CALL_BUTTON_DOWN_PIN 45
#define CALL_BUTTON_UP_PIN 47

#define CALL_BUTTON_DOWN_LIGHT_PIN 51
#define CALL_BUTTON_UP_LIGHT_PIN 49

long encoderPosition = -999;
long lastEncoderPosition = -999;
boolean lastEncoderButtonPressed = false;
void setup() {

  //Fix the matrix orientation, I installed them upside down
  for(int i=0; i< sizeof(lcdDef) / 8; i++ ){     
     flipLcdDef(lcdDef[i]);  
  }
    
  encoderPosition = abs((knob.read() / 4));
  lastEncoderPosition = encoderPosition;
  lastEncoderButtonPressed = false;
  initLcd(elevatorFloorIndicator);
  initLcd(callStationFloorIndicator);
  pinMode(DOVER_BUZZ_PIN, OUTPUT);
  pinMode(DINNER_BELL_PIN, OUTPUT);
  pinMode(ENCODER_PUSH_SWITCH_PIN, INPUT_PULLUP);

  pinMode(CALL_BUTTON_DOWN_PIN, INPUT_PULLUP);
  pinMode(CALL_BUTTON_UP_PIN, INPUT_PULLUP);

  pinMode(CALL_BUTTON_DOWN_LIGHT_PIN, OUTPUT);
  pinMode(CALL_BUTTON_UP_LIGHT_PIN, OUTPUT);
  digitalWrite(DOVER_BUZZ_PIN, 0);
  digitalWrite(DINNER_BELL_PIN, 0);
  digitalWrite(CALL_BUTTON_DOWN_LIGHT_PIN, 0);
  digitalWrite(CALL_BUTTON_UP_LIGHT_PIN, 0);
  //startDinnerBell();
  //startDoverBuzz();
}

void initLcd(LedControl& lc) {
  lc.shutdown(0,false);
  // Set brightness to a medium value
  lc.setIntensity(0,15 );
  // Clear the display
  lc.clearDisplay(0);
}

void drawLcd(byte def[], LedControl& lc) {
  lc.setRow(0,0,def[0]);
  lc.setRow(0,1,def[1]);
  lc.setRow(0,2,def[2]);
  lc.setRow(0,3,def[3]);
  lc.setRow(0,4,def[4]);
  lc.setRow(0,5,def[5]);
  lc.setRow(0,6,def[6]);
  lc.setRow(0,7,def[7]);
}



void flipLcdDef(byte a[8]) { 
  byte b[8];
  byte c[8];
  memset(b, 0, 8);
  memset(c, 0, 8);
  for(int i=0; i<8; i++) {
    b[i] = reverse(a[i]);
  }
  for(int i=0; i<8; i++) {
    c[i] = b[7-i];
  }
  
  memcpy(a, c, 8);
} 

byte reverse(byte in) {
 byte out = 0;
 for(int i=0; i < 8; i++)
 out |= ((in >> i) & 1) << (7 - i);
 return out;
}



int callStationFloor = 0;
int elevatorFloor = 0;
int elevatorDirection = 0;
boolean changedFloors;
boolean arrivedAtDestination;
unsigned long startedMovingTime = 0;
boolean downCallActive = false;
boolean upCallActive = false;

boolean isInFloorSelectMode = false;
int selectedFloor = 0;


long floorFromEncoderPosition(long encoderPosition) {
   long modulo = (encoderPosition % numFloors) ;
   return (numFloors + modulo) % numFloors;
}


byte* floorDef(int number) {
 
  return lcdDef[number];
}

boolean callPending() {
  return upCallActive || downCallActive;
}

int floorPassingDelayPlan[ sizeof(lcdDef) / 8];
void setupFloorDelayPlan() {
  int startFloor = elevatorFloor;
  int endFloor = callStationFloor;

  int numFloorsToTravel = abs(endFloor - startFloor);
  int accel = 100;
  int slowestSpeed = 1000;
  int fastestSpeed = 150;
  int velocity = 1000;
  int floorsTraveled = 0;
  for(int i = startFloor; i != endFloor; i = i + 1 * elevatorDirection) {
      if(floorsTraveled < max(numFloorsToTravel - 5, numFloorsToTravel / 2)) {
        velocity -= accel;   
      }
      else {
        velocity += accel;
      }
      if(velocity > slowestSpeed) {
        velocity = slowestSpeed;
      }
      if(velocity < fastestSpeed) {
        velocity = fastestSpeed;
      }
      floorPassingDelayPlan[i] = velocity;
      floorsTraveled++;
  }
}

//1000 900 800 700 800 900 1000
#define FLOOR_CHANGE_DELAY 1000
unsigned long startChangingFloorsMillis = -9999;
void updateElevatorDirectionAndFloor() {
   
   if(elevatorDirection == 0 && !callPending()) {
      return; //Nothing to do
   }
   if(elevatorDirection == 0 && callPending() && (callStationFloor < elevatorFloor)) {
      // start moving down
      elevatorDirection = -1;
      startChangingFloorsMillis = millis();
      setupFloorDelayPlan();
        
   }
   else if(elevatorDirection == 0 && callPending() && (callStationFloor > elevatorFloor)) {
      // start moving up
      elevatorDirection = 1;
      startChangingFloorsMillis = millis();
      setupFloorDelayPlan(); 
   }

   //Update floor if timer expired
   else if( millis() - startChangingFloorsMillis > floorPassingDelayPlan[elevatorFloor] ) {
      elevatorFloor += elevatorDirection;
      if(elevatorFloor == callStationFloor) {
         elevatorDirection = 0;
      } 
      else {
        startChangingFloorsMillis = millis(); // Keep going up
      }
   }
   



   

      


  
     
}

boolean downButtonIsPressed() {
  return digitalRead(CALL_BUTTON_DOWN_PIN) == 0;
}
boolean upButtonIsPressed() {
  return digitalRead(CALL_BUTTON_UP_PIN) == 0;
}
boolean encoderButtonIsPressed() {
  return digitalRead(ENCODER_PUSH_SWITCH_PIN) == 0;
}

void updateCalls() {
  if(elevatorFloor == callStationFloor) {
    downCallActive = false;
    upCallActive = false;
  }
  acceptNewCalls();
  
}

void acceptNewCalls() {
   if(elevatorDirection != 0  || callStationFloor == elevatorFloor) {
     return;
   }      
   if(downButtonIsPressed()) {
     downCallActive = true;
     return;
   }
   if(upButtonIsPressed() ) {
     upCallActive = true;
     return;
   }
}




void updateFloorSelection() {
  
  static int lastSelectedFloor = 0;
  if( elevatorDirection != 0 || callPending()) {
     return;
  }

  //Commit when floor is pressed
  if( isInFloorSelectMode && encoderButtonIsPressed() ) {
     callStationFloor = selectedFloor;
     isInFloorSelectMode = false;
     return;
  }

  encoderPosition = (knob.read() / 4) * -1;
  selectedFloor = floorFromEncoderPosition(encoderPosition);

  if( !isInFloorSelectMode && lastSelectedFloor != selectedFloor) {
    isInFloorSelectMode = true;
  }
  lastSelectedFloor = selectedFloor;
}





void updateState() {
  updateCalls();
  updateElevatorDirectionAndFloor();
  updateFloorSelection(); 
}


void loop(){
   updateState();
   renderState(); 
}

//End State updating

//Rendering


void renderState() {
  renderLcds();
  renderButtonLights();
  renderDoverBuzz();
  renderDinnerBell();
}


void renderDoverBuzz() {
  static int lastElevatorFloor = 0;
  turnOffDoverBuzzIfNeeded();
  if( lastElevatorFloor != elevatorFloor) {
    startDoverBuzz(); 
  }
  lastElevatorFloor = elevatorFloor;
}


boolean dinnerBellIsOn = false;
unsigned long dinnerBellStartTime = 0;

void stopDinnerBellIfNeeded() {
   if(dinnerBellIsOn && (millis() - dinnerBellStartTime > 100)) {
     digitalWrite(DINNER_BELL_PIN, 0);
     dinnerBellIsOn = false;
   }
}

void renderDinnerBell() {
  static boolean wasMoving = false;
  stopDinnerBellIfNeeded();
  boolean isMoving = (elevatorDirection != 0  || callPending());
  
  if(!isMoving && wasMoving) {
     startDinnerBell();
  }
  wasMoving = isMoving;
}


byte blank[8];
boolean selectionModeShowing = true;
void renderLcds() {
  static int lastElevatorFloor = -999;
  if(elevatorFloor != lastElevatorFloor) {
     drawLcd(lcdDef[elevatorFloor], elevatorFloorIndicator);
  }
  lastElevatorFloor = elevatorFloor;

  static unsigned long lastBlinkTime = -999;
  if( isInFloorSelectMode ) {
     byte* frame;
     if( millis() - lastBlinkTime > ( selectionModeShowing ? 500 : 50)) {
         selectionModeShowing = !selectionModeShowing;
         lastBlinkTime = millis();
     }
     if(selectionModeShowing) {
         frame = lcdDef[selectedFloor];
     } 
     else {
         frame = blank;
     }
     
     drawLcd(frame, callStationFloorIndicator);
  }
  else {
    drawLcd(lcdDef[callStationFloor], callStationFloorIndicator);
     
  }
}


void renderButtonLights() {
  
  if(upButtonIsPressed() || upCallActive) {
     digitalWrite(CALL_BUTTON_UP_LIGHT_PIN, 1);
  }
  else {
     digitalWrite(CALL_BUTTON_UP_LIGHT_PIN, 0);
    
  }
  if(downButtonIsPressed() || downCallActive) {
     digitalWrite(CALL_BUTTON_DOWN_LIGHT_PIN, 1);
  }
  else {
     digitalWrite(CALL_BUTTON_DOWN_LIGHT_PIN, 0);    
  }
}


boolean doverBuzzing = false;
unsigned long doverBuzzStartTime = 0;
#define DOVER_BUZZ_DELAY 100
void turnOffDoverBuzzIfNeeded() {
   if(doverBuzzing && (millis() - doverBuzzStartTime > DOVER_BUZZ_DELAY)) {
     digitalWrite(DOVER_BUZZ_PIN, 0);
     doverBuzzing = false;
   }
}
void startDoverBuzz() {
  doverBuzzing = true;
  doverBuzzStartTime = millis();
  digitalWrite(DOVER_BUZZ_PIN, 1);
}


void startDinnerBell() {
  dinnerBellIsOn = true;
  dinnerBellStartTime = millis();
  digitalWrite(DINNER_BELL_PIN, 1);
}
//End Rendering
