#!/bin/bash
set -e

#rm cmake/Makefile
#rm cmake/compile_commands.json
#rm cmake/cmake_install.cmake
#rm cmake/CMakeCache.txt
#rm -Rf cmake/CMakeFiles

cd cmake
cmake .
make
