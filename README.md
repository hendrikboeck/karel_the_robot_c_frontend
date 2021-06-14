<p align="center"><img width=64px src=".github/karel.png"></p>
<h1 align="center">Karel The Robot - C Frontend</h1>

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/5270727151dc4891aa3867dfbe80663a)](https://www.codacy.com/gh/hendrikboeck/karel_the_robot_c_frontend/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=hendrikboeck/karel_the_robot_c_frontend&amp;utm_campaign=Badge_Grade) ![C](https://img.shields.io/badge/c-99+-blue.svg) [![License](https://img.shields.io/badge/license-GPL_v3.0-blue.svg)](https://opensource.org/licenses/GPL-3.0) [![GitHub release](https://img.shields.io/github/release/hendrikboeck/karel_the_robot_c_frontend.svg)](https://github.com/hendrikboeck/karel_the_robot_c_frontend/releases/) [![Maintenance](https://img.shields.io/badge/Maintained%3F-yes-green.svg)](https://github.com/hendrikboeck/karel_the_robot_c_frontend/graphs/commit-activity)

- [1. General](#1-general)
  - [1.1. Abstract](#11-abstract)
  - [1.2. How it works](#12-how-it-works)
- [2. Create a Starter-Project](#2-create-a-starter-project)
- [3. Example Program](#3-example-program)
- [4. Acknowledgements](#4-acknowledgements)

# 1. General

## 1.1. Abstract

Karel The Robot was invented in th 1970s by Richard E. Pattis at Standford Univeristy. Karel The Robot is a program, that should make the intruduction to coding for newcomers and beginners more simple. Its aim is to teach basic principles such as top-down programming and establish them from the beginning. Futhermore is learning programming with Karel The Robot a way more visual and rewarding experience then just printing out some strings and numbers onto the command-line.

Also see [hendrikboeck/karel_the_robot_python3_backend](https://github.com/hendrikboeck/karel_the_robot_python3_backend).

## 1.2. How it works

The frontend connects to the PBE-pipe via a TCP-socket (`tcp/14480`). As a JSON-Writer and JSON-Reader the [simplejson-c](https://github.com/hendrikboeck/simplejson-c) library is used. Currently StarterProjects for CLion and simple CMake projects are supported. StarterProjects can either be built from the repository (see [2. Create a Starter-Project](#2-create-a-starter-project)) or downloaded from the [Releases](https://github.com/hendrikboeck/karel_the_robot_c_frontend/releases) section.

# 2. Create a Starter-Project

You can create various StarterProjects for various Operating Systems through the `Makefile`. 

```sh
make <target>
```

Values for `<target>`:

- `all`: creates CMake and CLion Projects and creates them as dynamic and static.
- `cmake_static`: creates a CMake Project, where all libraries are precompiled and staticly linked.
- `cmake_dynamic`: creates a CMake Project, where all libraries and resources are downloaded and compiled in the build-process.
- `clion_static`: creates a CLion Project, where all libraries are precompiled and staticly linked.
- `clion_dynamic`: creates a CLion Project, where all libraries and resources are downloaded and compiled in the build-process.

# 3. Example Program

The header-file `karel.h` can be found at `res/karel.h`.

```c
#include "karel.h"

void turnRight();
void moveToWall();

int main(void) {
  loadWorld("LivingRoom");

  moveToWall();
  turnLeft();
  move();
  turnRight();
  ...

  return 0;
}

void turnRight() {
  turnLeft();
  turnLeft();
  turnLeft();
}

void moveToWall() {
  while(frontIsClear())
    move();
}
```

# 4. Acknowledgements

- Karel The Robot by Richard E. Pattis at Stanford University
- [KarelLearnsC](https://github.com/OTHRegensburgMedieninformatik/KarelLearnsC) by [OTHRegensburgMedieninformatik](https://github.com/OTHRegensburgMedieninformatik)
