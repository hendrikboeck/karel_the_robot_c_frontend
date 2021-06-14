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

cmake_minimum_required(VERSION 3.6)

project(karel LANGUAGES C VERSION 0.1)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE_INIT "Release")

set(PBE_RELEASE v0.1)
set(PBE_BRANCH stable)

## LIBRARY ##

include(FetchContent)
FetchContent_Declare(
  simplejsonlib
  GIT_REPOSITORY https://github.com/hendrikboeck/simplejson-c.git
  GIT_TAG        develop
)
FetchContent_MakeAvailable(simplejsonlib)

## PROJECT ##

include_directories(
  ${PROJECT_BINARY_DIR}/_deps/simplejsonlib-src/src/headerFiles
  ${PROJECT_SOURCE_DIR}/src/headerFiles
  ${PROJECT_SOURCE_DIR}
)
file(GLOB ALL_SRCS
  "${PROJECT_SOURCE_DIR}/src/sourceFiles/*.c"
)

add_library(karel STATIC ${ALL_SRCS})
add_dependencies(karel simplejson)
target_link_libraries(karel simplejson)

if(NOT EXISTS ${CMAKE_BINARY_DIR}/PBE_PKG)
  if (WIN32)
    file(DOWNLOAD https://github.com/hendrikboeck/karel_the_robot_python3_backend/releases/download/${PBE_RELEASE}-${PBE_BRANCH}/PBE_PKG_${PBE_RELEASE}_win_x64.zip ${CMAKE_BINARY_DIR}/PBE_PKG_${PBE_RELEASE}_win_x64.zip)
    file(ARCHIVE_EXTRACT INPUT ${CMAKE_BINARY_DIR}/PBE_PKG_${PBE_RELEASE}_win_x64.zip)
  else()
    file(DOWNLOAD https://github.com/hendrikboeck/karel_the_robot_python3_backend/releases/download/${PBE_RELEASE}-${PBE_BRANCH}/PBE_PKG_${PBE_RELEASE}_linux_x64.tar.gz ${CMAKE_BINARY_DIR}/PBE_PKG_${PBE_RELEASE}_linux_x64.tar.gz)
    file(ARCHIVE_EXTRACT INPUT ${CMAKE_BINARY_DIR}/PBE_PKG_${PBE_RELEASE}_linux_x64.tar.gz)
  endif()
endif()

add_subdirectory(examples)
add_subdirectory(tests)
