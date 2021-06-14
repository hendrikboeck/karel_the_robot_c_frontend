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

## You do not have to change version
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

## Change helloworld to your desired project-name
project(helloworld VERSION 1.0 LANGUAGES C)

## Specify where all your .h-files are
set(INCLUDE_DIRECTORIES .)

## Add all src (*.c) files you want to compile after ALL_SRCS
set(SRC_FILES helloworld.c)

################################################################################
##                         !! DO NOT EDIT BELOW !!                            ##
################################################################################
set(CMAKE_C_STANDARD 99)
set(C_STANDARD_REQUIRED 99)
set(CMAKE_BUILD_TYPE_INIT "Release")
set(TARGETNAME ${PROJECT_NAME})

set(PBE_RELEASE v0.1)
set(PBE_BRANCH stable)
if(NOT EXISTS ${CMAKE_BINARY_DIR}/PBE_PKG)
  file(DOWNLOAD https://github.com/hendrikboeck/karel_the_robot_python3_backend/releases/download/${PBE_RELEASE}-${PBE_BRANCH}/PBE_PKG_${PBE_RELEASE}_win_x64.zip ${CMAKE_BINARY_DIR}/PBE_PKG_${PBE_RELEASE}_win_x64.zip)
  file(ARCHIVE_EXTRACT INPUT ${CMAKE_BINARY_DIR}/PBE_PKG_${PBE_RELEASE}_win_x64.zip)
endif()

include_directories(
  ${INCLUDE_DIRECTORIES}
  ${PROJECT_BINARY_DIR}/_deps/simplejsonlib-src/src/headerFiles
  ${PROJECT_BINARY_DIR}/_deps/karellib-src/src/headerFiles
  ${PROJECT_BINARY_DIR}/_deps/cmocka-src/src/include
)
file(GLOB ALL_SRCS ${SRC_FILES})

include(FetchContent)
FetchContent_Declare(
  karellib
  GIT_REPOSITORY https://github.com/hendrikboeck/karel_the_robot_c_frontend.git
  GIT_TAG        develop
)
FetchContent_MakeAvailable(karellib)

add_executable(${TARGETNAME} ${ALL_SRCS})
add_dependencies(${TARGETNAME} karel)
target_compile_features(${TARGETNAME} PRIVATE c_std_99)
target_link_libraries(${TARGETNAME} PRIVATE karel ws2_32)