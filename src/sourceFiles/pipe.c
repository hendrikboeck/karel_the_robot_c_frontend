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

#include "pipe.h"

void pipeInit() {
  globals.id     = 0;
  globals.client = tcpclient_new();
  tcpclient_connect(globals.client);

  atexit(pipeClose);
}

void pipeClose() {
  tcpclient_close(globals.client);
}

Object pipeReceive(int64_t id) {
  if (globals.client == NULL) FATAL_ERROR("pipe has not been initialized yet.");

  strview_t  json   = tcpclient_receive(globals.client);
  JSONReader reader = jsonreader_new(json);
  Dict       data   = jsonreader_getDict(reader);
  if (object_getInt64(dict_get(data, "id")) != id)
    FATAL_ERROR("ID's of messages did not match");

  Object result = object_copy(dict_get(data, "result"));
  jsonreader_del(reader);

  return result;
}

int64_t pipeSend(strview_t commandName, Dict args) {
  if (globals.client == NULL) FATAL_ERROR("pipe has not been initialized yet.");

  Dict    command = dict_new();
  int64_t id      = globals.id++;
  Object  oargs   = (args == NULL) ? object_new(NULL) : object_new(args);

  dict_set(command, str_copy("id"), object_new((int64_t)id));
  dict_set(command, str_copy("function"), object_new(str_copy(commandName)));
  dict_set(command, str_copy("args"), oargs);

  JSONWriter writer = jsonwriter_new(command);
  tcpclient_send(globals.client, jsonwriter_getStrView(writer));

  jsonwriter_del(writer);
  dict_del(command);
  return id;
}
