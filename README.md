<p align="center"><img width=64px src=".github/karel.png"></p>
<h1 align="center">Karel The Robot - C Frontend</h1>

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/5270727151dc4891aa3867dfbe80663a)](https://www.codacy.com/gh/hendrikboeck/karel_the_robot_c_frontend/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=hendrikboeck/karel_the_robot_c_frontend&amp;utm_campaign=Badge_Grade) ![C](https://img.shields.io/badge/c-11+-blue.svg) [![License](https://img.shields.io/badge/license-GPL_v3.0-blue.svg)](https://opensource.org/licenses/GPL-3.0) [![GitHub release](https://img.shields.io/github/release/hendrikboeck/karel_the_robot_python3_backend.svg)](https://github.com/hendrikboeck/karel_the_robot_python3_backend/releases/) [![Maintenance](https://img.shields.io/badge/Maintained%3F-yes-green.svg)](https://github.com/hendrikboeck/karel_the_robot_c_frontend/graphs/commit-activity)

- [1. General](#1-general)
  - [1.1. Abstract](#11-abstract)
- [2. Create a Starter-Project](#2-create-a-starter-project)
  - [2.1. CMake](#21-cmake)

# 1. General

## 1.1. Abstract

This is a frontend for the "Karel The Robot - Universal Backend" project.

# 2. Create a Starter-Project

## 2.1. CMake

If you want to create a C-project based on the CMake build system you can use the integrated `ExternalProject_Add` function of CMake. Donwload [`karel.h`](karel.h) to your folder with your header-files. Just add the following lines to your `CMakeLists.txt`.

```cmake
cmake_minimum_required(VERSION 3.6)

project(<projectname> LANGUAGES C VERSION 0.1)
set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE_INIT "Release")

include(ExternalProject)
ExternalProject_Add(
  karel
  
  GIT_REPOSITORY  https://github.com/hendrikboeck/karel_the_robot_c_frontend.git
  GIT_TAG         stable

  INSTALL_COMMAND ""

  CMAKE_ARGS
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
)
ExternalProject_Get_Property(karel install_dir)

find_library(karel ${install_dir})

include_directories(
  <path to folder with .h-files>
)

add_executable(<targetname> <src-files>)
add_dependencies(<targetname> karel)
target_link_libraries(<targetname> libkarel)
```
