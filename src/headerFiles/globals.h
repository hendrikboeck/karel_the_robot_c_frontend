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

#ifndef _KAREL_GLOBALS_H
#define _KAREL_GLOBALS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "simplejson/_internal.h"

#define DEFAULT_SERVER_ADDR "127.0.0.1"
#define DEFAULT_SERVER_PORT 14480

struct _TcpClient;

struct __GTypeWrapper {
  str_t              serverAddr;
  int32_t            serverPort;
  struct _TcpClient* client;
  int64_t            id;
};

extern struct __GTypeWrapper globals;

#ifdef __cplusplus
}
#endif

#endif  // _JSON_GLOBALS_H