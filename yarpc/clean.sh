# Copyright 2017 lilde90. All Rights Reserved.
# Author: Pan Li (panli.me@gmail.com)
#!/bin/bash
#

if [ -f Makefile ]; then
  make clean
  cd base
  if [ -f Makefile ]; then
    make clean
  fi
  cd ..
  cd core
  if [ -f Makefile ]; then
    make clean
  fi
  cd ..
fi

rm -f CMakeCache.txt
rm -rf CMakeFiles
rm -f Makefile
rm -f cmake_install.cmake

rm -f ./*/CMakeCache.txt
rm -rf ./*/CMakeFiles
rm -f ./*/Makefile
rm -f ./*/cmake_install.cmake
rm -rf ./*/*.a

