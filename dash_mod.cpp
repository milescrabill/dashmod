#include "dash_mod.h"

// Dash will run forward until a collision is detected with the IR sensors, at which point Dash stops, backs up, turns, and again starts running
void DashMod::dashBump(void) {
  
  setupIRsensors();
  
  unsigned long init_time = millis();
  unsigned long current_time = millis();

  // auto_flag must be 1, if not, an all stop has been called and the auto mode should exit
  while (millis() - init_time < 20000 && auto_flag == 1){
    // run around
    dashRun(40,0);
    current_time = millis();
    while (millis()-current_time < 50) {} // Give yourself time to run!
    setEyeColor(100, 0, 0);
    dashPacketHandler(); // listen for other commands
    
    //if collision, back up, turn around, try again
    if (detectCollisionLeft(baseline_IR_left * .04) || detectCollisionRight(baseline_IR_right * .04)) {
      unsigned long bump_time = millis();


      // Stop the robot
      while (millis() - bump_time < 500 && auto_flag == 1) {
      setEyeColor(0, 100, 0);
      allStop();
      //dashPacketHandler();

      }
      
      // Back up
      while (millis() - bump_time < 1500 && auto_flag == 1) {
      dashRun(-40,0);
      //dashPacketHandler();
 
      }

      // Turn around
      while (millis() - bump_time < 2500 && auto_flag == 1) {
      dashRun(40,150);
      //dashPacketHandler();
  
      }
      
    }
  }
  allStop();
}

void DashMod::dashStopIR(){
  setupIRsensors();
  
  unsigned long init_time = millis();
  unsigned long current_time = millis();

  setEyeColor(0, 100, 0);
  // auto_flag must be 1, if not, an all stop has been called and the auto mode should exit
  while (millis() - init_time < 20000 && auto_flag == 1){
//    setEyeColor(0, 0, 0);
    dashRun(40,0);
    current_time = millis();
    while (millis()-current_time < 50) {}
    dashPacketHandler(); // listen for other commands
    
    if (detectCollisionLeft(baseline_IR_left * .04) || detectCollisionRight(baseline_IR_right * .04)) {
      unsigned long bump_time = millis();

      // stop
      while (millis() - bump_time < 2000 && auto_flag == 1) {
        setEyeColor(0, 0, 255);
        allStop();   
        //dashPacketHandler();
      }
    }
  }
  allStop();
  setEyeColor(100, 0, 0);
}

void DashMod::dashStopAmbient(){  
  baseline_ambient = readAmbientLight();
  
  unsigned long init_time = millis();
  unsigned long current_time = millis();
  
  setEyeColor(100, 0, 0);

  // auto_flag must be 1, if not, an all stop has been called and the auto mode should exit
  while (millis() - init_time < 20000 && auto_flag == 1){
    dashRun(40,0);    
    current_time = millis();
    while (millis()-current_time < 50) {}
//    setEyeColor(0, 0, 100);
    dashPacketHandler(); // listen for other commands

    // detect collision checks (ambient < baseline - thresh)
    if (detectCollisionAmbient(baseline_ambient * .5)) {
      unsigned long bump_time = millis();

      // stop
      while (millis() - bump_time < 2000 && auto_flag == 1) {
        setEyeColor(100, 0, 100);
        allStop();
        //dashPacketHandler();
      }
    }
  }
  allStop();
  setEyeColor(100, 0, 0);
}

void DashMod :: setEyesIR() {
  int scaled_left_IR = map(readLeftIRsensor(), readLeftIRsensor() - baseline_IR_left * .25, baseline_IR_left + baseline_IR_left * .25, 0, 100);
  int scaled_right_IR = map(readRightIRsensor(), readRightIRsensor() - baseline_IR_right * .25, baseline_IR_right + baseline_IR_right * .25, 0, 100); 

  setEyeColor(scaled_left_IR, 0, scaled_right_IR);
}

//// detects a collision on the left side of the robot by comparing current IR reading to the baseline
//// takes a threshold variable as an input to set sensitivity
boolean DashMod::detectCollisionLeft(int thresh)
{
  if (readLeftIRsensor() < baseline_IR_left-thresh) {
    return true;
  } else {
    return false;
  }
}

//// detects a collision on the right side of the robot by comparing current IR reading to the baseline
//// takes a threshold variable as an input to set sensitivity
boolean DashMod::detectCollisionRight(int thresh)
{
  if(readRightIRsensor() < baseline_IR_right-thresh){
    return true;
  } else {
    return false;
  }
}

//// detects a collision on the left side of the robot by comparing current ambient light reading to the baseline
//// takes a threshold variable as an input to set sensitivity
boolean DashMod::detectCollisionAmbient(int thresh)
{
  if (readAmbientLight() < baseline_ambient - thresh) {
    return true;
  } else {
    return false;
  }
}

void DashMod::dashStopFlex(){  
  baseline_flex = readFlex();
  
  unsigned long init_time = millis();
  unsigned long current_time = millis();
  
  setEyeColor(100, 0, 0);

  // auto_flag must be 1, if not, an all stop has been called and the auto mode should exit
  while (millis() - init_time < 20000 && auto_flag == 1){
    dashRun(40,0);    
    current_time = millis();
    while (millis()-current_time < 50) {}
//    setEyeColor(0, 0, 100);
    dashPacketHandler(); // listen for other commands

    // detect collision checks (flex < baseline - thresh)
    if (detectCollisionFlex(baseline_flex * .25)) {
      unsigned long bump_time = millis();

      // stop
      while (millis() - bump_time < 2000 && auto_flag == 1) {
        setEyeColor(100, 0, 100);
        allStop();
        //dashPacketHandler();
      }
    }
  }
  allStop();
  setEyeColor(100, 0, 0);
}

// we have our flex sensor plugged into A5
int DashMod::readFlex() {
  return analogRead(A5);
}

//// detects a collision on the left side of the robot by comparing current flex sensor reading to the baseline
//// takes a threshold variable as an input to set sensitivity
boolean DashMod::detectCollisionFlex(int thresh)
{
  if (readFlex() < baseline_flex - thresh) {
    return true;
  } else {
    return false;
  }
}
