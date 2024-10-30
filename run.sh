#!/bin/bash

# Get the directory of the script
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

# Define the path to the build directory
BUILD_DIR="$SCRIPT_DIR/build"

# Define the executable file
EXECUTABLE="RivalGrounds"

# Define the build script
BUILD_SCRIPT="../build.sh"

# Function to build the project
build_project() {
    echo "$EXECUTABLE does not exist. Building..."
    if ! "$BUILD_SCRIPT"; then
        echo "Build failed. Exiting."
        exit 1
    fi
}

# Function to run the executable
run_executable() {
    if [ ! -f "$EXECUTABLE" ]; then
        echo "$EXECUTABLE not found after building. Exiting."
        exit 1
    fi
    echo "Running $EXECUTABLE..."
    ./$EXECUTABLE &
}

# Main script
cd "$BUILD_DIR" || { echo "Failed to change directory to $BUILD_DIR"; exit 1; }

if [ ! -f "$EXECUTABLE" ]; then
    build_project
fi

run_executable

