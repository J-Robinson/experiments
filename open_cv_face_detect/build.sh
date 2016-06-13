#!/bin/bash

rm -fr release
mkdir -p release/bin
cp cascades/* release/bin

cd release
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..
make
