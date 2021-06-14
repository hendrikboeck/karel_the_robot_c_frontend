cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(examples VERSION 1.0 LANGUAGES C)

file(
  COPY        ${CMAKE_SOURCE_DIR}/res/karel.h
  DESTINATION ${CMAKE_BINARY_DIR}
)

include_directories(${CMAKE_BINARY_DIR})

add_executable(helloworld helloworld.c)
target_compile_features(helloworld PRIVATE c_std_99)
target_link_libraries(helloworld PRIVATE karel simplejson)
if (WIN32)
target_link_libraries(helloworld PRIVATE ws2_32)
endif()

add_executable(testerror testerror.c)
target_compile_features(testerror PRIVATE c_std_99)
target_link_libraries(testerror PRIVATE karel simplejson)
if (WIN32)
target_link_libraries(testerror PRIVATE ws2_32)
endif()

add_executable(testroom testroom.c)
target_compile_features(testroom PRIVATE c_std_99)
target_link_libraries(testroom PRIVATE karel simplejson)
if (WIN32)
target_link_libraries(testroom PRIVATE ws2_32)
endif()
