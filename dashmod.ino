/*
basic Dash firmware. 
*/
//libraries
#include <EEPROM.h>
#include <DashBot.h>
#include <Serial.h>
#include "dash_mod.h"

DashMod myrobot; //gyro, motors, controller, LEDs, eyes

void setup() {
  myrobot.auto_flag = 1;
  myrobot.dashRadioSetup();
  myrobot.dashBumpFlex();
}

void loop() {
  myrobot.dashPacketHandler();
}
