cmake_minimum_required(VERSION 3.6)

project(karel LANGUAGES C VERSION 0.1)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE_INIT "Release")

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

# file(COPY ${PROJECT_SOURCE_DIR}/PBE_PKG DESTINATION ${CMAKE_BINARY_DIR})
# add_executable(example example.c)
# add_dependencies(example karel)
# target_link_libraries(
#   example
# 
#   ${CMAKE_BINARY_DIR}/libkarel.a
#   ${install_dir}/src/simplejson-build/libsimplejson.a
#   ws2_32
# )
