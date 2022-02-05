#!/bin/bash

mkdir dist
mkdir dist/target

#
# CENTRAL SERVER
#
echo -e "\033[0;33m[*] build target..\033[0m"
cd dist/target
cmake ../../src/target
make
echo -e "\033[0;33mdone.\033[0m"