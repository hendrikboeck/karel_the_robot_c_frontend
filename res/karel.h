/******************************************************************************/
/* karel_the_robot_c_frontend                                                 */
/* Copyright (C) 2021  Hendrik Boeck <hendrikboeck.dev@protonmail.com>        */
/*                                                                            */
/* This program is free software: you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation, either version 3 of the License, or          */
/* (at your option) any later version.                                        */
/*                                                                            */
/* This program is distributed in the hope that it will be useful,            */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of             */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              */
/* GNU General Public License for more details.                               */
/*                                                                            */
/* You should have received a copy of the GNU General Public License          */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>.      */
/******************************************************************************/

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