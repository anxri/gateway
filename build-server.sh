#!/bin/bash

mkdir dist
mkdir dist/server

echo -e "\033[0;33m[*] build server..\033[0m"
cd dist/server
cmake ../../src/server
make
echo -e "\033[0;33mdone.\033[0m"