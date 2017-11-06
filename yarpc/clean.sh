# Copyright 2017 lilde90. All Rights Reserved.
# Author: Pan Li (panli.me@gmail.com)
#!/bin/bash
#

rm -f CMakeCache.txt
rm -rf CMakeFiles
rm -f Makefile
rm -f cmake_install.cmake

rm -f ./base/CMakeCache.txt
rm -rf ./base/CMakeFiles
rm -f ./base/Makefile
rm -f ./base/cmake_install.cmake

if [ -f Makefile ]; then
  make clean
fi
