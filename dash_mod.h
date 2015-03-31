#ifndef DASHMOD_H
#define DASHMOD_H

#include <DashBot.h>

class DashMod : public DashBot {
public:
  int auto_flag;
  int baseline_ambient;
  int baseline_flex;
  
  void dashStopAmbient(void);
  void dashStopIR(void);
  void dashBump(void);
  void dashStopFlex(void);
  
  void setEyesIR(void);
  int readFlex(void);
  
  boolean detectCollisionLeft(int);
  boolean detectCollisionRight(int);
  boolean detectCollisionAmbient(int);
  boolean detectCollisionFlex(int);
};

#endif
