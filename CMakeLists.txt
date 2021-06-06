cmake_minimum_required(VERSION 3.6)

project(karel LANGUAGES C VERSION 0.1)
set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE_INIT "Release")

## LIBRARY ##

include(ExternalProject)
ExternalProject_Add(
  simplejson

  GIT_REPOSITORY    https://github.com/hendrikboeck/simplejson-c.git
  GIT_TAG           develop

  INSTALL_COMMAND   ""

  CMAKE_ARGS
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
)
ExternalProject_Get_Property(simplejson install_dir)

include_directories(
  ${install_dir}/src/simplejson/src/headerFiles
)
find_library(simplejson ${install_dir})

## PROJECT ##

include_directories(
  ${PROJECT_SOURCE_DIR}/src/headerFiles
)
file(GLOB ALL_SRCS
  "${PROJECT_SOURCE_DIR}/src/sourceFiles/*.c"
)

add_library(${TARGET_NAME} STATIC ${ALL_SRCS})
add_dependencies(${TARGET_NAME} simplejson)
target_link_libraries(${TARGET_NAME} libsimplejson)