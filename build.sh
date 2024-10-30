#!/bin/bash

# Get the directory of the script
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

# Define the path to the build directory
BUILD_DIR="$SCRIPT_DIR/build"

# Function to initialize submodules
init_submodules() {
    if [ ! -d "build/vendor" ]; then
        mkdir build/vendor
        echo "Adding submodules..."
        git submodule add -f https://github.com/Dav1dde/glad.git build/vendor/glad
        git submodule add -f https://github.com/alaingalvan/crosswindow.git build/vendor/CrossWindow
    fi
    git submodule update --init --recursive
}

# Function to build the project
build_project() {
    rm -rf CMakeCache.txt CMakeFiles cmake_install.cmake Makefile
    cmake ../
    make
}

# Main script
cd "$SCRIPT_DIR" || { echo "Failed to change directory to $SCRIPT_DIR"; exit 1; }

init_submodules

cd "$BUILD_DIR" || { echo "Failed to change directory to $BUILD_DIR"; exit 1; }

build_project

