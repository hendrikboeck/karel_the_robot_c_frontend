BUILDDIR = build-starterprojects

CMAKE_DYN_WIN64_BUILDDIR    = ${BUILDDIR}/cmake_dyn_win64/StarterProject
CMAKE_STATIC_WIN64_BUILDDIR = ${BUILDDIR}/cmake_static_win64/StarterProject
CLION_DYN_WIN64_BUILDDIR    = ${BUILDDIR}/clion_dyn_win64/StarterProject
CLION_STATIC_WIN64_BUILDDIR = ${BUILDDIR}/clion_static_win64/StarterProject

CMAKE_DYN_UNIX64_BUILDDIR    = ${BUILDDIR}/cmake_dyn_unix64/StarterProject
CMAKE_STATIC_UNIX64_BUILDDIR = ${BUILDDIR}/cmake_static_unix64/StarterProject
CLION_DYN_UNIX64_BUILDDIR    = ${BUILDDIR}/clion_dyn_unix64/StarterProject
CLION_STATIC_UNIX64_BUILDDIR = ${BUILDDIR}/clion_static_unix64/StarterProject

.PHONY: all_windows
all_windows: cmake_dynamic_windows cmake_static_windows clion_dynamic_windows clion_static_windows

.PHONY: all_unixlike
all_unixlike: cmake_dynamic_unixlike cmake_static_unixlike clion_dynamic_unixlike clion_static_unixlike

cmake_dynamic_windows: 
	mkdir -p ${CMAKE_DYN_WIN64_BUILDDIR}
	cp -r PBE_PKG ${CMAKE_DYN_WIN64_BUILDDIR}
	cp res/cmake/cmake_dyn_win64.cmake ${CMAKE_DYN_WIN64_BUILDDIR}/CMakeLists.txt
	cp examples/helloworld.c ${CMAKE_DYN_WIN64_BUILDDIR}/
	cp res/karel.h ${CMAKE_DYN_WIN64_BUILDDIR}/

cmake_static_windows: 
	mkdir -p ${CMAKE_STATIC_WIN64_BUILDDIR} ${CMAKE_STATIC_WIN64_BUILDDIR}/lib
	cmake -S . -B build -G "MinGW Makefiles"
	cmake --build build --config Release
	cp -r PBE_PKG ${CMAKE_STATIC_WIN64_BUILDDIR}/
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

