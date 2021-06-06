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

#ifndef _KAREL_KAREL_IMPL_H
#define _KAREL_KAREL_IMPL_H

#include <stdlib.h>

#include "pipe.h"
#include "simplejson/_internal.h"

void __startPBEProcess();
Object __executeCommand(strview_t commandName, Dict args);

void loadWorld(strview_t name);

void move();
void turnLeft();
void pickBeeper();
void putBeeper();

int32_t frontIsClear();
int32_t frontIsBlocked();
int32_t rightIsClear();
int32_t rightIsBlocked();
int32_t leftIsClear();
int32_t leftIsBlocked();
int32_t beeperInBag();
int32_t noBeeperInBag();
int32_t beeperPresent();
int32_t noBeeperPresent();
int32_t facingNorth();
int32_t notFacingNorth();
int32_t facingEast();
int32_t notFacingEast();
int32_t facingSouth();
int32_t notFacingSouth();
int32_t facingWest();
int32_t notFacingWest();

#endif  // _KAREL_KAREL_IMPL_H