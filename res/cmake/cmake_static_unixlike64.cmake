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
)
file(GLOB ALL_SRCS ${SRC_FILES})

add_executable(${TARGETNAME} ${ALL_SRCS})
target_compile_features(${TARGETNAME} PRIVATE c_std_99)
target_link_libraries(${TARGETNAME} 
  ${PROJECT_SOURCE_DIR}/lib/libkarel.a
  ${PROJECT_SOURCE_DIR}/lib/libsimplejson.a
)
