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

#ifndef _KAREL_PIPE_H
#define _KAREL_PIPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "globals.h"
#include "simplejson/jsonreader.h"
#include "simplejson/jsonwriter.h"
#include "tcp_client.h"

void pipeInit();
void pipeClose();

Object  pipeReceive(int64_t id);
int64_t pipeSend(strview_t commandName, Dict args);

#ifdef __cplusplus
}
#endif

#endif  // _KAREL_PIPE_H