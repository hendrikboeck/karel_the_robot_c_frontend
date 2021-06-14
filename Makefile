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

ifeq ($(OS),Windows_NT)
PLATFORM = windows
else
PLATFORM = unixlike
UNAME_S  = $(shell uname -s)
ifeq ($(UNAME_S),Linux)
SUBSYSTEM = linux
else
SUBSYSTEM = macos
endif
endif

PBE_RELEASE = v0.1
PBE_BRANCH  = stable

BUILDDIR = build-starterprojects

CMAKE_DYN_WIN64_BUILDDIR    = ${BUILDDIR}/cmake_dyn_win64/StarterProject
CMAKE_STATIC_WIN64_BUILDDIR = ${BUILDDIR}/cmake_static_win64/StarterProject
CLION_DYN_WIN64_BUILDDIR    = ${BUILDDIR}/clion_dyn_win64/StarterProject
CLION_STATIC_WIN64_BUILDDIR = ${BUILDDIR}/clion_static_win64/StarterProject

CMAKE_DYN_UNIX64_BUILDDIR    = ${BUILDDIR}/cmake_dyn_unix64/StarterProject
CMAKE_STATIC_UNIX64_BUILDDIR = ${BUILDDIR}/cmake_static_unix64/StarterProject
CLION_DYN_UNIX64_BUILDDIR    = ${BUILDDIR}/clion_dyn_unix64/StarterProject
CLION_STATIC_UNIX64_BUILDDIR = ${BUILDDIR}/clion_static_unix64/StarterProject

.PHONY: all
all: cmake_dynamic cmake_static clion_dynamic clion_static

.PHONY: cmake_dynamic
cmake_dynamic: cmake_dynamic_${PLATFORM}

.PHONY: cmake_static
cmake_static: cmake_static_${PLATFORM}

.PHONY: clion_dynamic
clion_dynamic: clion_dynamic_${PLATFORM}

.PHONY: clion_static
clion_static: clion_static_${PLATFORM}

.PHONY: release
release: release_${PLATFORM}

cmake_dynamic_windows:
	mkdir -p ${CMAKE_DYN_WIN64_BUILDDIR}
	cp res/cmake/cmake_dyn_win64.cmake ${CMAKE_DYN_WIN64_BUILDDIR}/CMakeLists.txt
	cp examples/helloworld.c ${CMAKE_DYN_WIN64_BUILDDIR}/
	cp res/karel.h ${CMAKE_DYN_WIN64_BUILDDIR}/

cmake_static_windows:
	mkdir -p ${CMAKE_STATIC_WIN64_BUILDDIR} ${CMAKE_STATIC_WIN64_BUILDDIR}/lib
	cmake -S . -B build -G "MinGW Makefiles"
	cmake --build build --config Release
	cp -r build/PBE_PKG ${CMAKE_STATIC_WIN64_BUILDDIR}/
	cp build/libkarel.a ${CMAKE_STATIC_WIN64_BUILDDIR}/lib/
	cp build/_deps/simplejsonlib-build/libsimplejson.a ${CMAKE_STATIC_WIN64_BUILDDIR}/lib/
	cp res/cmake/cmake_static_win64.cmake ${CMAKE_STATIC_WIN64_BUILDDIR}/CMakeLists.txt
	cp examples/helloworld.c ${CMAKE_STATIC_WIN64_BUILDDIR}/
	cp res/karel.h ${CMAKE_STATIC_WIN64_BUILDDIR}/

clion_dynamic_windows: cmake_dynamic_windows 
	mkdir -p ${BUILDDIR}/clion_dyn_win64/
	cp -r ${CMAKE_DYN_WIN64_BUILDDIR} ${CLION_DYN_WIN64_BUILDDIR}
	cp -r res/.idea_clion_dyn_win64 ${CLION_DYN_WIN64_BUILDDIR}/.idea

clion_static_windows: cmake_static_windows 
	mkdir -p ${BUILDDIR}/clion_static_win64/
	cp -r ${CMAKE_STATIC_WIN64_BUILDDIR} ${CLION_STATIC_WIN64_BUILDDIR}
	cp -r res/.idea_clion_static_win64 ${CLION_STATIC_WIN64_BUILDDIR}/.idea

release_windows: all
	mkdir -p ${BUILDDIR}/releases
# CMAKE_STATIC
	cd ${BUILDDIR}/cmake_static_win64; jar -cMf ../releases/StarterProject_CMake_Static_Windows_x64.zip StarterProject
# CMAKE_DYNAMIC
	cd ${BUILDDIR}/cmake_dyn_win64; jar -cMf ../releases/StarterProject_CMake_Dynamic_Windows_x64.zip StarterProject
# CLION_STATIC
	cd ${BUILDDIR}/clion_static_win64; jar -cMf ../releases/StarterProject_CLion_Static_Windows_x64.zip StarterProject
# CLION_DYNAMIC
	cd ${BUILDDIR}/clion_dyn_win64; jar -cMf ../releases/StarterProject_CLion_Dynamic_Windows_x64.zip StarterProject
# ALL
	cd ${BUILDDIR}; jar -cMf releases/StarterProject_All_Windows_x64.zip clion_dyn_win64 clion_static_win64 cmake_dyn_win64 cmake_static_win64

clean_unixlike:
	rm -rf ${BUILDDIR}/*

cmake_dynamic_unixlike:
	mkdir -p ${CMAKE_DYN_UNIX64_BUILDDIR}
	cp res/cmake/cmake_dyn_unixlike64.cmake ${CMAKE_DYN_UNIX64_BUILDDIR}/CMakeLists.txt
	cp examples/helloworld.c ${CMAKE_DYN_UNIX64_BUILDDIR}/
	cp res/karel.h ${CMAKE_DYN_UNIX64_BUILDDIR}/

cmake_static_unixlike:
	mkdir -p ${CMAKE_STATIC_UNIX64_BUILDDIR}/lib/
	cmake -S . -B build
	cmake --build build --config Release
	cp -r build/PBE_PKG ${CMAKE_STATIC_UNIX64_BUILDDIR}/
	cp build/libkarel.a ${CMAKE_STATIC_UNIX64_BUILDDIR}/lib/
	cp build/_deps/simplejsonlib-build/libsimplejson.a ${CMAKE_STATIC_UNIX64_BUILDDIR}/lib/
	cp res/cmake/cmake_static_unixlike64.cmake ${CMAKE_STATIC_UNIX64_BUILDDIR}/CMakeLists.txt
	cp examples/helloworld.c ${CMAKE_STATIC_UNIX64_BUILDDIR}/
	cp res/karel.h ${CMAKE_STATIC_UNIX64_BUILDDIR}/

clion_dynamic_unixlike: cmake_static_unixlike
	mkdir -p ${BUILDDIR}/clion_dyn_unix64/
	cp -r ${CMAKE_DYN_UNIX64_BUILDDIR} ${CLION_DYN_UNIX64_BUILDDIR}
	cp -r res/.idea_clion_dyn_unix64 ${CLION_DYN_UNIX64_BUILDDIR}/.idea

clion_static_unixlike: cmake_static_unixlike
	mkdir -p ${BUILDDIR}/clion_static_unix64/
	cp -r ${CMAKE_STATIC_UNIX64_BUILDDIR} ${CLION_STATIC_UNIX64_BUILDDIR}
	cp -r res/.idea_clion_static_unix64 ${CLION_STATIC_UNIX64_BUILDDIR}/.idea

release_unixlike: release_${SUBSYSTEM}

.ONESHELL: release_linux
release_linux: all
	mkdir -p ${BUILDDIR}/releases
# CMAKE_STATIC
	cd ${BUILDDIR}/cmake_static_unix64
	tar -zcvf StarterProject_CMake_Static_Linux_x64.tar.gz StarterProject
	zip -r StarterProject_CMake_Static_Linux_x64.zip StarterProject
	mv StarterProject_CMake_Static_Linux_x64.* ../releases
# CMAKE_DYNAMIC
	cd ../cmake_dyn_unix64
	tar -zcvf StarterProject_CMake_Dynamic_Linux_x64.tar.gz StarterProject
	zip -r StarterProject_CMake_Dynamic_Linux_x64.zip StarterProject
	mv StarterProject_CMake_Dynamic_Linux_x64.* ../releases
# CLION_STATIC
	cd ${BUILDDIR}/clion_static_unix64
	tar -zcvf StarterProject_CLion_Static_Linux_x64.tar.gz StarterProject
	zip -r StarterProject_CLion_Static_Linux_x64.zip StarterProject
	mv StarterProject_CLion_Static_Linux_x64.* ../releases
# CLION_DYNAMIC
	cd ../clion_dyn_unix64
	tar -zcvf StarterProject_CLion_Dynamic_Linux_x64.tar.gz StarterProject
	zip -r StarterProject_CLion_Dynamic_Linux_x64.zip StarterProject
	mv StarterProject_CLion_Dynamic_Linux_x64.* ../releases
# ALL
	cd ..
	tar -zcvf StarterProject_All_Linux_x64.tar.gz cmake_dyn_unix64 cmake_static_unix64 clion_dyn_unix64 clion_static_unix64
	zip -r StarterProject_All_Linux_x64.zip cmake_dyn_unix64 cmake_static_unix64 clion_dyn_unix64 clion_static_unix64
	mv StarterProject_All_Linux_x64.* releases

release_macos: all
	mkdir -p ${BUILDDIR}/releases
# CMAKE_STATIC
	cd ${BUILDDIR}/cmake_static_unix64; tar -zcvf StarterProject_CMake_Static_MacOS_x64.tar.gz StarterProject
	cd ${BUILDDIR}/cmake_static_unix64; zip -r StarterProject_CMake_Static_MacOS_x64.zip StarterProject
	mv ${BUILDDIR}/cmake_static_unix64/StarterProject_CMake_Static_MacOS_x64.* ${BUILDDIR}/releases
# CMAKE_DYNAMIC
	cd ${BUILDDIR}/cmake_dyn_unix64; tar -zcvf StarterProject_CMake_Dynamic_MacOS_x64.tar.gz StarterProject
	cd ${BUILDDIR}/cmake_dyn_unix64; zip -r StarterProject_CMake_Dynamic_MacOS_x64.zip StarterProject
	mv ${BUILDDIR}/cmake_dyn_unix64/StarterProject_CMake_Dynamic_MacOS_x64.* ${BUILDDIR}/releases
# CLION_STATIC
	cd ${BUILDDIR}/clion_static_unix64; tar -zcvf StarterProject_CLion_Static_MacOS_x64.tar.gz StarterProject
	cd ${BUILDDIR}/clion_static_unix64; zip -r StarterProject_CLion_Static_MacOS_x64.zip StarterProject
	mv ${BUILDDIR}/clion_static_unix64/StarterProject_CLion_Static_MacOS_x64.* ${BUILDDIR}/releases
# CLION_DYNAMIC
	cd ${BUILDDIR}/clion_dyn_unix64; tar -zcvf StarterProject_CLion_Dynamic_MacOS_x64.tar.gz StarterProject
	cd ${BUILDDIR}/clion_dyn_unix64; zip -r StarterProject_CLion_Dynamic_MacOS_x64.zip StarterProject
	mv ${BUILDDIR}/clion_dyn_unix64/StarterProject_CLion_Dynamic_MacOS_x64.* ${BUILDDIR}/releases
# ALL
	cd ${BUILDDIR}; tar -zcvf StarterProject_All_MacOS_x64.tar.gz cmake_dyn_unix64 cmake_static_unix64 clion_dyn_unix64 clion_static_unix64
	cd ${BUILDDIR}; zip -r StarterProject_All_MacOS_x64.zip cmake_dyn_unix64 cmake_static_unix64 clion_dyn_unix64 clion_static_unix64
	mv ${BUILDDIR}/StarterProject_All_MacOS_x64.* ${BUILDDIR}/releases
