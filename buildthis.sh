#!/bin/bash

BUILD_DIR="build"

if [ -d "$BUILD_DIR" ]; then
    rm -rf "$BUILD_DIR";
fi

mkdir build
cd build
cmake ..
make
cd ..

mv "$BUILD_DIR/run" run
rm -rf "$BUILD_DIR"

echo "Success!!!"