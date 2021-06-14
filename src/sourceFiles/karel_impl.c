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

#include "karel_impl.h"

void startPBEProcess() {
#ifdef _WIN32
  system(".\\PBE_PKG\\run_karel_pbe.bat");
#else
  system("./PBE_PKG/run_karel_pbe.sh");
  sleep(1);
#endif
}

Object executeCommand(strview_t commandName, Dict args) {
  int64_t id     = pipeSend(commandName, args);
  Object  result = pipeReceive(id);

  if (object_isStr(result)) {
    StringBuffer sbuf = stringbuffer_new();
    stringbuffer_put(sbuf, "PBE-Error: ");
    stringbuffer_put(sbuf, object_getStr(result));
    if (str_equal(object_getStr(result), "ActionExecutionError"))
      stringbuffer_put(
          sbuf,
          ", for further information evaluate the ErrorWindow in the PBE.");
    sys_errorExit(EXIT_FAILURE, stringbuffer_get(sbuf));
  }

  return result;
}

void loadWorld(strview_t name) {
  startPBEProcess();
  pipeInit();

  Dict args = dict_new();
  dict_set(args, str_copy("map"), object_new(str_copy(name)));
  object_del(executeCommand("loadWorld", args));
}

void move() {
  object_del(executeCommand("move", NULL));
}

void turnLeft() {
  object_del(executeCommand("turnLeft", NULL));
}

void pickBeeper() {
  object_del(executeCommand("pickBeeper", NULL));
}

void putBeeper() {
  object_del(executeCommand("putBeeper", NULL));
}

int32_t frontIsClear() {
  Object  obj    = executeCommand("frontIsClear", NULL);
  int32_t result = (int32_t)object_getBool(obj);

  object_del(obj);
  return result;
}

int32_t frontIsBlocked() {
  return !frontIsClear();
}

int32_t rightIsClear() {
  Object  obj    = executeCommand("rightIsClear", NULL);
  int32_t result = (int32_t)object_getBool(obj);

  object_del(obj);
  return result;
}

int32_t rightIsBlocked() {
  return !rightIsClear();
}

int32_t leftIsClear() {
  Object  obj    = executeCommand("leftIsClear", NULL);
  int32_t result = (int32_t)object_getBool(obj);

  object_del(obj);
  return result;
}

int32_t leftIsBlocked() {
  return !leftIsClear();
}

int32_t beeperInBag() {
  Object  obj    = executeCommand("beeperInBag", NULL);
  int32_t result = (int32_t)object_getBool(obj);

  object_del(obj);
  return result;
}

int32_t noBeeperInBag() {
  return !beeperInBag();
}

int32_t beeperPresent() {
  Object  obj    = executeCommand("beeperPresent", NULL);
  int32_t result = (int32_t)object_getBool(obj);

  object_del(obj);
  return result;
}

int32_t noBeeperPresent() {
  return !beeperPresent();
}

int32_t facingNorth() {
  Object  obj    = executeCommand("facingNorth", NULL);
  int32_t result = (int32_t)object_getBool(obj);

  object_del(obj);
  return result;
}

int32_t notFacingNorth() {
  return !facingNorth();
}

int32_t facingEast() {
  Object  obj    = executeCommand("facingEast", NULL);
  int32_t result = (int32_t)object_getBool(obj);

  object_del(obj);
  return result;
}

int32_t notFacingEast() {
  return !facingEast();
}

int32_t facingSouth() {
  Object  obj    = executeCommand("facingSouth", NULL);
  int32_t result = (int32_t)object_getBool(obj);

  object_del(obj);
  return result;
}

int32_t notFacingSouth() {
  return !facingSouth();
}

int32_t facingWest() {
  Object  obj    = executeCommand("facingWest", NULL);
  int32_t result = (int32_t)object_getBool(obj);

  object_del(obj);
  return result;
}

int32_t notFacingWest() {
  return !facingWest();
}