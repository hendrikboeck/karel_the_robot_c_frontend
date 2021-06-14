################################################################################
# karel_the_robot_c_frontend                                                   #
# Copyright (C) 2021  Hendrik Boeck <hendrikboeck.dev@protonmail.com>          #
#                                                                              #
# This program is free software: you can redistribute it and/or modify         #
# it under the terms of the GNU General Public License as published by         #
# the Free Software Foundation, either version 3 of the License, or            #
# (at your option) any later version.                                          #
#                                                                              #
# This program is distributed in the hope that it will be useful,              #
# but WITHOUT ANY WARRANTY; without even the implied warranty of               #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                #
# GNU General Public License for more details.                                 #
#                                                                              #
# You should have received a copy of the GNU General Public License            #
# along with this program.  If not, see <http://www.gnu.org/licenses/>.        #
################################################################################

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(karel_test VERSION 1.0 LANGUAGES C)

# DOWNLOAD CMOCKA AND MAKE AVAILABLE
#
include(FetchContent)
FetchContent_Declare(
  cmocka
  GIT_REPOSITORY https://git.cryptomilk.org/projects/cmocka.git
  GIT_TAG        cmocka-1.1.5
  GIT_SHALLOW    1
)

set(WITH_STATIC_LIB ON CACHE BOOL "CMocka: Build with a static library" FORCE)
set(WITH_CMOCKERY_SUPPORT OFF CACHE BOOL "CMocka: Install a cmockery header" FORCE)
set(WITH_EXAMPLES OFF CACHE BOOL "CMocka: Build examples" FORCE)
set(UNIT_TESTING OFF CACHE BOOL "CMocka: Build with unit testing" FORCE)
set(PICKY_DEVELOPER OFF CACHE BOOL "CMocka: Build with picky developer flags" FORCE)

FetchContent_MakeAvailable(cmocka)

# BUILD TEST EXE
#
include_directories(.)
add_executable(karel_test run_cmocka_tests.c)
add_dependencies(karel_test cmocka)
target_compile_features(karel_test PRIVATE c_std_11)
target_link_libraries(karel_test PRIVATE cmocka-static karel simplejson)
if (WIN32)
target_link_libraries(karel_test PRIVATE ws2_32)
endif()

add_executable(tcp_echo_server tcp_echo_server.c)
if (WIN32)
target_link_libraries(tcp_echo_server PRIVATE ws2_32)
endif()

# ADD TO TESTS
#
enable_testing()
add_test(NAME karel_test COMMAND karel_test)