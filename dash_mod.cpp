#include "dash_mod.h"

void DashMod::dashBump(){
  setupIRsensors();
  unsigned long init_time = millis();
  unsigned long current_time = millis();

  setEyeColor(0, 0, 255);
  // auto_flag must be 1, if not, an all stop has been called and the auto mode should exit
  while (millis() - init_time < 10000 && auto_flag == 1){
    dashRun(40,0);    
    current_time = millis();
    while (millis()-current_time < 50) {}
    setEyeColor(255, 0, 255);
    dashPacketHandler(); // listen for other commands

    // detect collision checks (IRsensor < baseline - thresh)
    if (detectCollisionLeft(baseline_IR_left * (-3.0)) || detectCollisionRight(baseline_IR_right * (-3.0))) {
      unsigned long bump_time = millis();

      // stop
      while (millis() - bump_time < 2000 && auto_flag == 1) {
        allStop();
        //dashPacketHandler();
      }
    }
  }
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
