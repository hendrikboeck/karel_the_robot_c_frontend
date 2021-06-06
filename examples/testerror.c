#include "karel.h"

int main(void)
{
  loadWorld("TestRoom");

  move();
  move(); // walk into wall
  // pickBeeper(); // pick beeper, that does not exist
  
  return 0;
}
