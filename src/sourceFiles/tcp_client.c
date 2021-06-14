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

#include "tcp_client.h"

TCPClient tcpclient_new() {
  TCPClient self = PNEW(TCPClient);

  memset(&self->server, 0, sizeof(self->server));
  self->sock = -1;
  self->buf  = NEW_ARR(byte_t, TCP_MAX_PKG_SIZE);
  return self;
}

TCPClient tcpclient_del(TCPClient self) {
  tcpclient_close(self);
  DEL(self->buf);
  DEL(self);
  return NULL;
}

void tcpclient_connect(TCPClient self) {
  // create socket
#ifdef _WIN32
  self->wVersionRequested = MAKEWORD(1, 1);
  if (WSAStartup(self->wVersionRequested, &self->wsaData) != 0)
    FATAL_ERROR("tcpclient_connect: could not initialize winsock");
#endif  // _WIN32
  if (self == NULL) FATAL_ERROR("TCPClient == NULL");

  self->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (self->sock < 0) FATAL_ERROR("tcpclient_connect: could not create socket");

  // configure connection
  uint64_t addr = inet_addr(globals.serverAddr);
  memory_copyOnto(&self->server.sin_addr, &addr, sizeof(addr));
  self->server.sin_family = AF_INET;
  self->server.sin_port   = htons(globals.serverPort);

  // connect to server
  int32_t status = connect(self->sock, (struct sockaddr*)&self->server,
                           sizeof(self->server));
  if (status < 0)
    FATAL_ERROR(
        "tcpclient_connect: no connection to server could be established.");
}

void tcpclient_close(TCPClient self) {
  if (self->sock != -1) {
#ifdef _WIN32
    closesocket(self->sock);
    WSACleanup();
#else
    close(self->sock);
#endif
    self->sock = -1;
  }
  if (self->sock != -1) FATAL_ERROR("could not close tcp-socket");
}

void tcpclient_send(TCPClient self, strview_t data) {
  send(self->sock, data, strlen(data), 0);
}

strview_t tcpclient_receive(TCPClient self) {
  int32_t receivedSize = recv(self->sock, self->buf, TCP_MAX_PKG_SIZE, 0);
  if (receivedSize < 0)
    FATAL_ERROR("tcpclient_send: error on recv(), receivedSize < 0");

  self->buf[receivedSize] = 0;
  return self->buf;
}
