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

#include "globals_test.c"
#include "tcp_client_test.c"
#include "pipe_test.c"

int main(void) {
  // test globals.h
  printf("--------- RUNNING TESTS FOR 'globals.h' ---------\n");
  const struct CMUnitTest tests_globals[] = {
      cmocka_unit_test(test_globals_new)};
  int return_tests_globals = cmocka_run_group_tests(tests_globals, NULL, NULL);

  // test tcp_client.h
  system("./tests/tcp_echo_server &> /dev/null &");
  sleep(1);
  printf("\n--------- RUNNING TESTS FOR 'tcp_client.h' ---------\n");
  const struct CMUnitTest tests_tcp_client[] = {
      cmocka_unit_test(test_tcp_client_new),
      cmocka_unit_test(test_tcp_client_send_recv)};
  int return_tests_tcp_client =
      cmocka_run_group_tests(tests_tcp_client, NULL, NULL);

  // test tcp_client.h
  // system("./tests/tcp_echo_server &> /dev/null &");
  // sleep(1);
  printf("\n--------- RUNNING TESTS FOR 'pipe.h' ---------\n");
  const struct CMUnitTest tests_pipe[] = {cmocka_unit_test(test_pipe_all)};
  int return_tests_pipe = cmocka_run_group_tests(tests_pipe, NULL, NULL);

  

  return return_tests_globals + return_tests_tcp_client + return_tests_pipe;
}
