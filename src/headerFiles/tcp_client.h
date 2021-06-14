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

#ifndef _KAREL_TCP_CLIENT_H
#define _KAREL_TCP_CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#include <io.h>
#include <winsock.h>
#else
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "simplejson/_internal.h"
#include "simplejson/str.h"

#define TCP_MAX_PKG_SIZE 65535

#ifdef _WIN32
typedef SOCKET sock_t;
#else
typedef int32_t sock_t;
#endif

struct _TCPClient {
#ifdef _WIN32
  WORD    wVersionRequested;
  WSADATA wsaData;
#endif
  struct sockaddr_in server;
  sock_t             sock;
  byte_t*            buf;
};
typedef struct _TCPClient* TCPClient;

TCPClient tcpclient_new();
TCPClient tcpclient_del(TCPClient self);

void      tcpclient_connect(TCPClient self);
void      tcpclient_close(TCPClient self);
void      tcpclient_send(TCPClient self, strview_t data);
strview_t tcpclient_receive(TCPClient self);

#ifdef __cplusplus
}
#endif

#endif  // _KAREL_TCP_CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

struct _TCPClient;
typedef struct _TCPClient* TCPClient;

#ifdef __cplusplus
}
#endif
