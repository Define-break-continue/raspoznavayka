#!/bin/bash
#
# To run program after build, use build.sh -r
#

rm -rf build/
mkdir build
cd build/
cmake ../src/
make

[ "x$1" == "x-r" ] && ./raspoznavayka
