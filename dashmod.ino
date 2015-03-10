/*
basic Dash firmware. 
*/
//libraries
#include <EEPROM.h>
#include <DashBot.h>
#include "dash_mod.h"

DashMod myrobot; //gyro, motors, controller, LEDs, eyes

void setup() {
  myrobot.dashRadioSetup();
  myrobot.dashStopAmbient();
}

void loop(){
  myrobot.dashPacketHandler();
}
