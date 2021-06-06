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

file(COPY ${PROJECT_SOURCE_DIR}/PBE_PKG DESTINATION ${CMAKE_BINARY_DIR})

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
target_link_libraries(${TARGETNAME} PRIVATE karel)
