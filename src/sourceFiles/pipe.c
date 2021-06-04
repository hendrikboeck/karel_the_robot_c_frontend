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

void pipe_init() {
  globals.id     = 0;
  globals.client = tcpclient_new();
  tcpclient_connect(globals.client);
}

void pipe_close() {
  tcpclient_close(globals.client);
}

Object pipe_receive(int64_t id) {
  strview_t  json   = tcpclient_receive(globals.client);
  JSONReader reader = jsonreader_new(json);
  Dict       data   = jsonreader_getDict(reader);
  if (object_getInt64(dict_get(data, "id")) != id)
    __errorExit(EXIT_FAILURE, "id's of messages did not match.");

  Object result = object_copy(dict_get(data, "result"));
  jsonreader_del(reader);

  return result;
}

int64_t pipe_send(strview_t commandName, Dict args) {
  Dict    command = dict_new();
  int64_t id      = globals.id++;
  Object  oargs   = (args == NULL) ? object_new(NULL) : object_new(args);

  dict_set(command, "id", object_new(id));
  dict_set(command, "function", object_new(commandName));
  dict_set(command, "args", oargs);

  JSONWriter writer = jsonwriter_new(command);
  tcpclient_send(globals.client, jsonwriter_getStrView(writer));

  jsonwriter_del(writer);
  dict_del(command);
  return id;
}
