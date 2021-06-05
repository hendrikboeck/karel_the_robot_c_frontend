cmake_minimum_required(VERSION 3.6)
project(karel_cfe VERSION 0.1)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_C_STANDARD 11)

include(ExternalProject)
ExternalProject_Add(simplejson
  GIT_REPOSITORY  https://github.com/hendrikboeck/simplejson-c.git
  GIT_TAG         develop
  INSTALL_COMMAND ""
)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

include_directories(
  ${PROJECT_SOURCE_DIR}/src/headerFiles
  ${EXTERNAL_INSTALL_LOCATION}/include
)

file(GLOB ALL_SRCS
  "${PROJECT_SOURCE_DIR}/src/sourceFiles/*.c"
)

find_library(simplejson ${EXTERNAL_INSTALL_LOCATION})

add_library(${TARGET_NAME} STATIC ${ALL_SRCS})
add_dependencies(${TARGET_NAME} simplejson)
target_link_libraries(${TARGET_NAME} 
  libsimplejson
)
