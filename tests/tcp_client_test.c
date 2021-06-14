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

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
// <cmocka.h> --- below this comment
#include <cmocka.h>

#include "tcp_client.h"

static void test_tcp_client_new(void** state) {
  (void)state;

  TCPClient c_01 = tcpclient_new();

  assert_non_null(c_01);
  assert_non_null(c_01->buf);
  assert_int_equal(c_01->sock, -1);

  c_01 = tcpclient_del(c_01);
  assert_null(c_01);
}

static void test_tcp_client_send_recv(void** state) {
  (void)state;

  TCPClient c_01 = tcpclient_new();
  tcpclient_connect(c_01);

  for (int i = 0; i < 1000; i++) {
    tcpclient_send(c_01, "Hello World!");
    strview_t data = tcpclient_receive(c_01);
    assert_string_equal(data, "Hello World!");
  }

  tcpclient_close(c_01);
  c_01 = tcpclient_del(c_01);
  assert_null(c_01);
}
