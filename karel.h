#ifndef _KAREL_H
#define _KAREL_H

// World
extern void loadWorld(const char *name);

// Karel-Actions
extern void move();
extern void turnLeft();
extern void pickBeeper();
extern void putBeeper();

// Karel-Checks
extern int frontIsClear();
extern int frontIsBlocked();
extern int rightIsClear();
extern int rightIsBlocked();
extern int leftIsClear();
extern int leftIsBlocked();
extern int beeperInBag();
extern int noBeeperInBag();
extern int beeperPresent();
extern int noBeeperPresent();
extern int facingNorth();
extern int notFacingNorth();
extern int facingEast();
extern int notFacingEast();
extern int facingSouth();
extern int notFacingSouth();
extern int facingWest();
extern int notFacingWest();

#endif  // _KAREL_H