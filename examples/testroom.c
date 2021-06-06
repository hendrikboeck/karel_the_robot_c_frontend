#include "karel.h"

void turnRight() {
  turnLeft();
  turnLeft();
  turnLeft();
}

int main(void) {
  loadWorld("TestRoom");

  move();
  turnLeft();

  while (frontIsClear()) move();

  while (frontIsBlocked()) {
    turnLeft();
    move();
    turnRight();
  }

  int counter = 0;
  while (frontIsClear()) {
    while (beeperPresent()) {
      pickBeeper();
      counter++;
    }
    move();
  }

  while (counter > 0) {
    putBeeper();
    counter--;
  }

  return 0;
}
