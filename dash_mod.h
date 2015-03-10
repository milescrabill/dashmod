#ifndef DASHMOD_H
#define DASHMOD_H

#include <DashBot.h>

class DashMod : public DashBot {
public:
  int auto_flag;
  
  void dashBump();
  boolean detectCollisionLeft(int);
  boolean detectCollisionRight(int);
};

#endif
