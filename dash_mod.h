#ifndef DASHMOD_H
#define DASHMOD_H

#include <DashBot.h>

class DashMod : public DashBot {
public:
  int auto_flag;
  int baseline_ambient;
  
  void dashStopAmbient(void);
  boolean detectCollisionLeft(int);
  boolean detectCollisionRight(int);
  boolean detectCollisionAmbient(int);
};

#endif
